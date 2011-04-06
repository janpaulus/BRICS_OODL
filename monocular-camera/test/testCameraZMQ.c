#include <zmq.h>
#include <unicap.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <SDL/SDL.h>
#include <signal.h>
#include <getopt.h>
#include <unistd.h>
#include <assert.h>

extern char *optarg;

typedef struct PeerMode
{
    char ipaddress[30];
    char operationMode[15];
    char interactionMode[15];
} PeerMode;




int parseOptions(int argc, char *argv[], PeerMode *peerMode);

void visualizeImageData(const PeerMode *peerMode);

void generateImageData(const PeerMode *peerMode);





int main(int argc, char *argv[])
{

  PeerMode  *peerMode = (PeerMode*) malloc(sizeof(PeerMode));
  if(peerMode == NULL)
  {
    printf("ERROR ALLOCATING peer memory");
    exit(1);
  }

  if(parseOptions(argc, argv, peerMode) != 0)
  {
    printf("INVALID OPTION \n");
    exit(1);
  }


  if (strcmp(peerMode->operationMode,"consumer") == 0)
    visualizeImageData(peerMode);
  if (strcmp(peerMode->operationMode,"producer") == 0)
    generateImageData(peerMode);

  return 0;
}



// an application launches as a consumer
void visualizeImageData(const PeerMode *peerMode)
{
	void *context;
	void *consumer;

 //initialize zmq communication primitives
  context = zmq_init(1);

  if (strcmp(peerMode->interactionMode,"pub-sub") == 0)
  {
    consumer = zmq_socket(context, ZMQ_SUB);
    zmq_setsockopt(consumer, ZMQ_SUBSCRIBE, 0, 0);
  }

  else if (strcmp(peerMode->interactionMode,"req-rep") == 0)
  {
    consumer = zmq_socket(context, ZMQ_REQ);
  }
  int rc = zmq_connect(consumer, peerMode->ipaddress);
  assert(rc == 0);

  uint32_t width;
  uint32_t height;
  unsigned char *localDataBuffer;
  unicap_format_t localImageFormat;

  SDL_Surface *screen;
  SDL_Surface *rgb_surface;
  localDataBuffer = malloc(460800);
  //  Initialise SDL

  if (SDL_Init (SDL_INIT_VIDEO) < 0) {
    fprintf (stderr, "Failed to initialize SDL:  %s\n", SDL_GetError());
    exit (1);
  }
  screen = SDL_SetVideoMode (640, 360, 16 , SDL_SWSURFACE|SDL_ANYFORMAT);
  if (screen == NULL) {
    fprintf (stderr, "Unable to set video mode: %s\n", SDL_GetError ());
    SDL_Quit ();
    exit (1);
  }

//here in the loop should include send request first and then receive, when peer is in client consumer mode
//otherise when subscriber consumer mode it just receives.
  int quitSignal = 0;
  while(!quitSignal)
  {
    SDL_Event event;

    //create and initialize an empty request&receive message. It will grow dynamically
    if (strcmp(peerMode->interactionMode,"req-rep") == 0)
    {
      zmq_msg_t reqMsg;
      zmq_msg_init(&reqMsg);
      zmq_send(consumer, &reqMsg,0);
    }

    zmq_msg_t repMsg;
    zmq_msg_init(&repMsg);


    zmq_recv(consumer, &repMsg,0);

    if(localDataBuffer != NULL)
    {
      //read from msg (which is in the form of an array) to local data buffer

      //First 32bits make width of the image so need to read first 32 bits and move pointer
      memcpy (&width, zmq_msg_data(&repMsg), sizeof(uint32_t));
      localImageFormat.size.width = ntohl(width);

      //Second 32bits make height of the image so need to read second set of 32 bits and move pointer
      memcpy (&height, zmq_msg_data(&repMsg)+sizeof(uint32_t), sizeof(uint32_t));
      localImageFormat.size.height = ntohl(height);

      // The rest of the message is pixel data
      memcpy (localDataBuffer, zmq_msg_data(&repMsg)+2*sizeof(uint32_t), 460700);

    }

    rgb_surface = SDL_CreateRGBSurfaceFrom (
      localDataBuffer,           //  Pixel data
      localImageFormat.size.width,     //  Width
      localImageFormat.size.height,    //  Height
      16,//dest_format.bpp,            //  Depth
      1280,//dest_format.size.width * 3, //  Scanline pitch
      0, 0, 0, 0);                //  TODO RGBA mask

    //  Blit surface to screen

    SDL_BlitSurface (rgb_surface, NULL, screen, NULL);
    SDL_UpdateRect (screen, 0, 0, 0, 0);
    SDL_FreeSurface (rgb_surface);

    while (SDL_PollEvent (&event))
    {
      if (event.type == SDL_QUIT)
        quitSignal = 1;
    }

    zmq_msg_close(&repMsg);

  }

  free(localDataBuffer);
  SDL_Quit();

  return;
}


//an application launches as a server
void generateImageData(const PeerMode *peerMode)
{
	//created a context a publisher type socket
	void *context;
	void *provider;

  //printf("IP server %s\n",peerMode->ipaddress);
	//prepare context
	context = zmq_init(1);


  if (strcmp(peerMode->interactionMode,"pub-sub") == 0)
  {
    provider = zmq_socket(context, ZMQ_PUB);

  }
  else if (strcmp(peerMode->interactionMode,"req-rep") == 0)
  {
    provider = zmq_socket(context, ZMQ_REP);
  }

//For standalone server in pub-sub, req-rep or with proxyserver in between server
// and other subscribers (where one of the sub behaves like proxy server)
// behavior of the server is still the same, so it always uses "bind".
// In case of the broker, the situation is different, see below
  zmq_bind(provider, peerMode->ipaddress);

//In case one is using Broker in between clients and servers then server also need to use
//"connect" rather then "bind". Because they behave like clients for Broker
// zmq_connect(provider, peerMode->ipaddress);

//check whether there is a device connected
	int const maxDevices = 5;
  int deviceCount = 0;
  unicap_device_t devices[maxDevices];
  unicap_handle_t deviceHandle[maxDevices];
  int returnStatus = STATUS_SUCCESS;

  for(deviceCount = 0; SUCCESS(returnStatus) && (deviceCount<maxDevices); deviceCount++)
  {
    returnStatus = unicap_enumerate_devices(NULL, &devices[deviceCount], deviceCount);

    if(SUCCESS(returnStatus))
    {
      printf("Device identifier %d: %s\n", deviceCount, devices[deviceCount].identifier);
      printf("Device model name %d: %s\n", deviceCount, devices[deviceCount].model_name);
      printf("Device vendor name %d: %s\n", deviceCount, devices[deviceCount].vendor_name);
      printf("Device vendorId %d: %d\n", deviceCount, devices[deviceCount].vendor_id);
      printf("Device modelId %d: %d\n", deviceCount, devices[deviceCount].model_id);
      printf("Device device %d: %s\n", deviceCount, devices[deviceCount].device);
      printf("Device cpi_layer %d: %s\n", deviceCount, devices[deviceCount].cpi_layer);
      printf("----------------------------------------------------------- \n");
    }

    else
      break;

  }

  int i;
  int const maxImageFormats = 10;
  unicap_format_t deviceImageFormats[maxImageFormats];
  int formatCount = 0;
  int validFormat = 0;


//open all devices from the device list
  for(i=0; i < deviceCount; i++)
  {
    returnStatus = unicap_open(&deviceHandle[i], &devices[i]);
    if(SUCCESS(returnStatus))
          printf("Openning device number %d succeeded\n", i);
    else
      printf("Failed to open device %d\n", i);

    //enumerate formats for opened devices
    for (formatCount = 0; (formatCount <maxImageFormats); formatCount++)
    {
      returnStatus = unicap_enumerate_formats (deviceHandle[i], NULL, &deviceImageFormats[formatCount],
                                               formatCount);

      if(SUCCESS(returnStatus))
      {
        printf("Device supports format identification: %d: %s\n", formatCount, deviceImageFormats[formatCount].identifier);
        printf("horz stepping: %d: %d\n", formatCount, deviceImageFormats[formatCount].h_stepping);
        printf("vert stepping: %d: %d\n", formatCount, deviceImageFormats[formatCount].v_stepping);
        printf("bits per pixel: %d: %d\n", formatCount, deviceImageFormats[formatCount].bpp);
        printf("list size %d: %d\n", formatCount, deviceImageFormats[formatCount].size_count);
        printf("color format %d: %d\n", formatCount, deviceImageFormats[formatCount].fourcc);
        printf("resolutions width x height %d: %d x %d\n", formatCount,
               deviceImageFormats[formatCount].size.width,deviceImageFormats[formatCount].size.height);
        printf("Buffer type supported %d\n", deviceImageFormats[formatCount].buffer_type);
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n");
        validFormat++;
      }
      else
        printf("Can't enumerate formats\n");
    }
    printf("Number of formats supported by device '%s' is %d\n", devices[i].identifier, validFormat);
    printf("************************************************************** \n");
    printf("************************************************************** \n");

  }

    //set device format to the 1st format in the list for the 1st device
    // and to the 2nd format in the list for the 2nd device
    // later need to make it user-driven
    for(i=0; i < deviceCount; i++)
    {
      returnStatus = unicap_set_format(deviceHandle[i], &deviceImageFormats[0]);
      if(SUCCESS(returnStatus))
      {
        printf("Setting capture format for '%s'\n", devices[i].identifier);
        deviceImageFormats[0].buffer_type = UNICAP_BUFFER_TYPE_USER;
        printf("======================================================== \n \n");
      }
      else
        printf("Can not set chosen format %d for device %s \n", i, devices[i].identifier) ;
    }

    //get current format and print dimensions for it
    // 5th element in the array is just used to keep data about format
    // for calculations we use 1st elements
    for(i=0; i < deviceCount; i++)
    {
      returnStatus = unicap_get_format(deviceHandle[0], &deviceImageFormats[4]);
      if(SUCCESS(returnStatus))
      {
        printf("Device %s current format settings\n", devices[i].identifier);
        printf("Image bpp value: %d\n",  deviceImageFormats[4].bpp);
        printf("Image resolutions : %d x %d\n", deviceImageFormats[4].size.width,deviceImageFormats[4].size.height);
        printf("Buffer type: %d\n", deviceImageFormats[4].buffer_type);
        printf("Buffer size: %d\n", deviceImageFormats[4].buffer_size);
      }
      else
        printf("Can't get current format for %s \n", devices[i].identifier);
      printf("\n \n");
    }

   //Start capturing from the device
    unicap_data_buffer_t imageBuffer;

    imageBuffer.data = malloc(deviceImageFormats[0].buffer_size);
    imageBuffer.buffer_size = deviceImageFormats[0].buffer_size;
    printf("Allocated buffer memory for picture\n");

    if (!SUCCESS (unicap_start_capture (deviceHandle[0])))
    {
      fprintf (stderr, "Failed to start capture on device: %s\n",
               devices[1].identifier);
      exit (1);
    }
    else
      printf( "Capture successful!\n");

	while(1)
	{
		zmq_msg_t reqMsg;
		zmq_msg_t repMsg;
    unicap_data_buffer_t *returned_buffer;



    zmq_msg_init(&reqMsg);
    zmq_recv(provider, &reqMsg,0);
    zmq_msg_close(&reqMsg);

   //this queues buffer filled with image data in a queue
    if( !SUCCESS( unicap_queue_buffer( deviceHandle[0], &imageBuffer) ) )
    {
      fprintf( stderr, "Failed to queue buffer!\n" );
      exit( -1 );
    }
    //this waits till buffer is filled with image data and then dequeue it
    if( !SUCCESS( unicap_wait_buffer( deviceHandle[0], &returned_buffer ) ) )
    {
      fprintf( stderr, "Failed to wait for buffer!\n" );
      exit( -1 );
    }

    //create of the given size
		zmq_msg_init_size(&repMsg, imageBuffer.buffer_size+2*sizeof(uint32_t)); // memory for data and rectangle dimensions
    unsigned char *localDataBuffer = (unsigned char *)zmq_msg_data (&repMsg);
    //   printf("Msg size is %d", zmq_msg_size(&msg));

    /* Image width (uint32_t in network byte order) */
    uint32_t imageWidth = htonl (deviceImageFormats[0].size.width);
    memcpy (localDataBuffer, &imageWidth, sizeof (uint32_t));
    localDataBuffer += sizeof (uint32_t); //move the pointer 32 bits

    /* Image height (uint32_t in network byte order) */
    uint32_t imageHeight = htonl (deviceImageFormats[0].size.height);
    memcpy (localDataBuffer, &imageHeight, sizeof (uint32_t));
    localDataBuffer += sizeof (uint32_t); //move the pointer 32 bits

    //Copy pixel data into local buffer
    memcpy (localDataBuffer, imageBuffer.data, imageBuffer.buffer_size);

		//fill in the message with data
		zmq_send(provider,&repMsg,0);
		zmq_msg_close(&repMsg);

	}

  unicap_stop_capture( deviceHandle[0] );
  unicap_close(deviceHandle[0]);
  free( imageBuffer.data );

  return;
}


//Processes command-line options given to the program
int parseOptions(int argc, char *argv[], struct PeerMode *peerMode)
{

  int nextOption = 0;
  const char* const shortOptions = "hi:m:p:"; //constant pointer to constant char
  const struct option longOptions[] =
    {
      {"help", 0, NULL, 'h'},
      {"ipaddress", 1, NULL, 'i'},
      {"interactionmode", 1, NULL, 'm'},
      {"peermode", 1, NULL, 'p'},
      {NULL, 0, NULL, 0}
    };
  do
  {
    nextOption = getopt_long(argc, argv, shortOptions, longOptions, NULL);
    switch(nextOption)
    {
      case 'h':
        fprintf(stdout,
                "-h or --help  Prints this message \n"
                "-i <xxx> or --ipaddress <xxx> Set ip end-point to <xxx>\n"
                "-m <xxx> or --mode <xxx> Set mode to <xxx>, 'pub-sub', 'req-rep'\n"
		"-p <xxx> or --peermode <xxx> Set the peer behavior, 'producer' or 'consumer'\n");
        break;
      case 'i':
        strcpy(peerMode->ipaddress, optarg);
        break;
      case 'm':
        strcpy(peerMode->interactionMode,optarg);
        break;
      case 'p':
        strcpy(peerMode->operationMode,optarg);
        break;
      default:
        continue;
    }
  } while(nextOption != -1);

  return 0;
}
