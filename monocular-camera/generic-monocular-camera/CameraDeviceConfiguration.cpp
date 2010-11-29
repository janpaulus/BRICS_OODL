#include "CameraDeviceConfiguration.hpp"



CameraDeviceConfiguration::CameraDeviceConfiguration(): deviceCameraDevConf(NULL),
                                                        handleCameraDevConf(NULL),
                                                        returnStatus(STATUS_FAILURE),
							deviceConfPropertyCounter(0)
{
  std::cout << "Creating CameraDeviceConfiguration without arguments" << std::endl;

  videoFrameRate.min = 0.0;
  videoFrameRate.max = 0.0;
  videoGammaValue.min = 0.0;
  videoGammaValue.max = 0.0;
  videoSharpnessValue.min = 0.0;
  videoSharpnessValue.max = 0.0;
  lensFocus.min = 0.0;
  lensFocus.max = 0.0;
  lensZoom.min = 0.0;
  lensZoom.max = 0.0;
  lensIris.min = 0.0;
  lensIris.max = 0.0;
}


CameraDeviceConfiguration::CameraDeviceConfiguration(unicap_device_t *device, unicap_handle_t *handle): deviceCameraDevConf(device),
                                                                                                        handleCameraDevConf(handle),
                                                                                                        returnStatus(STATUS_FAILURE), 
                                                                                                        deviceConfPropertyCounter(0) 
{
  std::cout << "Creating CameraDeviceConfiguration with arguments" << std::endl;
  videoFrameRate.min = 0.0;
  videoFrameRate.max = 0.0;
  videoGammaValue.min = 0.0;
  videoGammaValue.max = 0.0;
  videoSharpnessValue.min = 0.0;
  videoSharpnessValue.max = 0.0;
  lensFocus.min = 0.0;
  lensFocus.max = 0.0;
  lensZoom.min = 0.0;
  lensZoom.max = 0.0;
  lensIris.min = 0.0;
  lensIris.max = 0.0;
}

//copy constructor
CameraDeviceConfiguration::CameraDeviceConfiguration(CameraDeviceConfiguration& cameradevconf) 
{

}

CameraDeviceConfiguration& CameraDeviceConfiguration::operator=(CameraDeviceConfiguration& cameradevconf) 
{
  if(&cameradevconf != this)
  {
    std::cout << "Inside CameraDeviceConfiguration assignment operator"<<std::endl;
  }
  return *this;
}



CameraDeviceConfiguration::~CameraDeviceConfiguration() 
{

  std::cout << "Destroying CameraDeviceConfiguration with arguments" << std::endl;

}


bool CameraDeviceConfiguration::getListOfDeviceProperties() 
{
  std::cout << "Inside CameraDeviceConfiguration getListOfDeviceProperties" << std::endl;
  unicap_property_t tempProperty = {0};
  

  
  while(SUCCESS(unicap_enumerate_properties( *handleCameraDevConf, NULL, &tempProperty, deviceConfPropertyCounter)))
  {

    listOfProperties.push_back(tempProperty);
    std::cout << listOfProperties.size()<< std::endl;
    std::cout << listOfProperties[deviceConfPropertyCounter].identifier<<std::endl;
    deviceConfPropertyCounter++;
    returnStatus = STATUS_SUCCESS;

  }

  if(listOfProperties.size() != 0 )
  {
    std::cout << "Number of properties " << deviceConfPropertyCounter<<std::endl;
    return true;
  }
  else
  {
    std::cout << "Property list is empty"<<std::endl;
    return false;
  }
 
}


// Make more efficient, so that I don't need to call enumerate_properties for each of the properties
// as it is done in if condition
bool CameraDeviceConfiguration::getVideoFrameRate(double &rate) 
{
  std::cout << "Inside CameraDeviceConfiguration getVideoFrameRate" << std::endl;
  const std::string propertyName ="frame rate";
  std::string charID;

  //check whether listOfProperties was filled in successfully and not empty
  if (SUCCESS(returnStatus) && (listOfProperties.size() != 0 ))
  {
    //here member variable deviceConfProperty is a total number of 
    //camera properties returned by getListOfDeviceProperties
    for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
    {
      //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
      //there are also menu, list, flag property types
      if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
      {
        //if range then check it for correct ID
        charID = listOfProperties[propertyCounter].identifier;
        //if ID == frame rate (as defined in unicap API) then return its current value
        if (charID == propertyName)
        {
          //check if the call succeeds 
          int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
          if( SUCCESS(returnValue) )
          {
            rate = listOfProperties[propertyCounter].value;
            //   std::cout << rate << std::endl;
            return true;
          }
        }
      }
      //if property is not of type "range" go to the beginning of the loop
    }
  }
  // if property list was not obtained successfully or was not filled in before through 
  //the call to getListOfDeviceProperties, call the method 
  else if (getListOfDeviceProperties() == true)
  {
    if (listOfProperties.size() != 0)
    {
      for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
      {
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
        {
          charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
          {
            int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
            if( SUCCESS(returnValue) )
            {
              rate = listOfProperties[propertyCounter].value;
              return true;
            }
          }
        }
        //if property is not of type "range" go to the beginning of the loop
      }
    }
    else
    {
      std::cout << "Property list is empty"<< std::endl;
      return false;
    }
  
  }
  // if neither of the above return error message
  else 
  {    
    std::cout << "Can not get property"<< std::endl;
    return false;
  }
}




bool CameraDeviceConfiguration::getVideoGammaValue(double &gamma) 
{

  std::cout << "Inside CameraDeviceConfiguration getVideoGammaValue" << std::endl;
  const std::string propertyName ="gamma";
  std::string charID;

  //check whether listOfProperties was filled in successfully and not empty
  if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
  {
    //here member variable deviceConfProperty is a total number of 
    //camera properties returned by getListOfDeviceProperties
    for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
    {
      //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
      //there are also menu, list, flag property types
      if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
      {
        //if range then check it for correct ID
        charID = listOfProperties[propertyCounter].identifier;
        //if ID == frame rate (as defined in unicap API) then return its current value
        if (charID == propertyName)
        {
          //check if the call succeeds 
          int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
          if( SUCCESS(returnValue) )
          {
            gamma = listOfProperties[propertyCounter].value;
            //   std::cout << rate << std::endl;
            return true;
          }
        }
      }
      //if property is not of type "range" go to the beginning of the loop
    }
  }
  // if property list was not obtained successfully or was not filled in before through 
  //the call to getListOfDeviceProperties, call the method 
  else if (getListOfDeviceProperties() == true)
  {
    if (listOfProperties.size() != 0)
    {
      for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
      {
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
        {
          charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
          {
            int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
            if( SUCCESS(returnValue) )
            {
              gamma = listOfProperties[propertyCounter].value;
              return true;
            }
          }
        }
        //if property is not of type "range" go to the beginning of the loop
      }
    }
    else
    {
      std::cout << "Property list is empty"<< std::endl;
      return false;
    }
  }
  // if neither of the above return error message
  else 
  {    
    std::cout << "Can not get property"<< std::endl;
    return false;
  }  
 
}

bool CameraDeviceConfiguration::getVideoSharpnessValue(double &sharpness) {

  std::cout << "Inside CameraDeviceConfiguration getVideoSharpnessValue" << std::endl;
  const std::string propertyName ="sharpness";
  std::string charID;

  //check whether listOfProperties was filled in successfully and not empty
  if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
  {
    //here member variable deviceConfProperty is a total number of 
    //camera properties returned by getListOfDeviceProperties
    for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
    {
      //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
      //there are also menu, list, flag property types
      if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
      {
	//if range then check it for correct ID
	charID = listOfProperties[propertyCounter].identifier;
	//if ID == frame rate (as defined in unicap API) then return its current value
	if (charID == propertyName)
	{
	  //check if the call succeeds 
	  int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
	  if( SUCCESS(returnValue) )
	  {
	    sharpness = listOfProperties[propertyCounter].value;
	    return true;
	  }
	}
      }
      //if property is not of type "range" go to the beginning of the loop
    }
  }
  // if property list was not obtained successfully or was not filled in before through 
  //the call to getListOfDeviceProperties, call the method 
  else if (getListOfDeviceProperties() == true)
  {
    if (listOfProperties.size() != 0)
    {
      for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
      {
	if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
	{
	  charID = listOfProperties[propertyCounter].identifier;
	  if (charID == propertyName)
	  {
	    int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
	    if( SUCCESS(returnValue) )
	    {
	      sharpness = listOfProperties[propertyCounter].value;
	      return true;
	    }
	  }
	}
	//if property is not of type "range" go to the beginning of the loop
      }
    }
    else
    {
      std::cout << "Property list is empty"<< std::endl;
      return false;
    }
  }
  // if neither of the above return error message
  else 
  {    
    std::cout << "Can not get property"<< std::endl;
    return false;
  }

}

bool CameraDeviceConfiguration::getLensFocus(double &focus) {

  std::cout << "Inside CameraDeviceConfiguration getLensFocus" << std::endl;
  const std::string propertyName ="focus";
  std::string charID;

  //check whether listOfProperties was filled in successfully and not empty
  if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
  {
    //here member variable deviceConfProperty is a total number of 
    //camera properties returned by getListOfDeviceProperties
    for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
    {
      //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
      //there are also menu, list, flag property types
      if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
      {
        //if range then check it for correct ID
        charID = listOfProperties[propertyCounter].identifier;
        //if ID == frame rate (as defined in unicap API) then return its current value
        if (charID == propertyName)
        {
          //check if the call succeeds 
          int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
          if( SUCCESS(returnValue) )
          {
            focus = listOfProperties[propertyCounter].value;
            return true;
          }
        }
      }
      //if property is not of type "range" go to the beginning of the loop
    }
  }
  // if property list was not obtained successfully or was not filled in before through 
  //the call to getListOfDeviceProperties, call the method 
  else if (getListOfDeviceProperties() == true)
  {
    if (listOfProperties.size() != 0)
    {
      for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
      {
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
        {
          charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
          {
            int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
            if( SUCCESS(returnValue) )
            {
              focus = listOfProperties[propertyCounter].value;
              return true;
            }
          }
        }
        //if property is not of type "range" go to the beginning of the loop
      }
    }
    else
    {
      std::cout << "Property list is empty"<< std::endl;
      return false;
    }
  }
  // if neither of the above return error message
  else 
  {    
    std::cout << "Can not get property"<< std::endl;
    return false;
  }

}

bool CameraDeviceConfiguration::getLensZoom(double &zoom) {

  std::cout << "Inside CameraDeviceConfiguration getLensZoom" << std::endl;
  const std::string propertyName ="zoom";
  std::string charID;

  //check whether listOfProperties was filled in successfully and not empty
  if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
  {
    //here member variable deviceConfProperty is a total number of 
    //camera properties returned by getListOfDeviceProperties
    for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
    {
      //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
      //there are also menu, list, flag property types
      if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
      {
        //if range then check it for correct ID
        charID = listOfProperties[propertyCounter].identifier;
        //if ID == frame rate (as defined in unicap API) then return its current value
        if (charID == propertyName)
        {
          //check if the call succeeds 
          int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
          if( SUCCESS(returnValue) )
          {
            zoom = listOfProperties[propertyCounter].value;
            return true;
          }
        }
      }
      //if property is not of type "range" go to the beginning of the loop
    }
  }
  // if property list was not obtained successfully or was not filled in before through 
  //the call to getListOfDeviceProperties, call the method 
  else if (getListOfDeviceProperties() == true)
  {
    if (listOfProperties.size() != 0)
    {
      for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
      {
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
        {
          charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
          {
            int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
            if( SUCCESS(returnValue) )
            {
              zoom = listOfProperties[propertyCounter].value;
              return true;
            }
          }
        }
        //if property is not of type "range" go to the beginning of the loop
      }
    }
    else
    {
      std::cout << "Property list is empty"<< std::endl;
      return false;
    }
  }
  // if neither of the above return error message
  else 
  {    
    std::cout << "Can not get property"<< std::endl;
    return false;
  }

}

bool CameraDeviceConfiguration::getLensIris(double &iris) {

  std::cout << "Inside CameraDeviceConfiguration getLensIris" << std::endl;
  const std::string propertyName ="iris";
  std::string charID;

  //check whether listOfProperties was filled in successfully and not empty
  if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
  {
    //here member variable deviceConfProperty is a total number of 
    //camera properties returned by getListOfDeviceProperties
    for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
    {
      //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
      //there are also menu, list, flag property types
      if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
      {
        //if range then check it for correct ID
        charID = listOfProperties[propertyCounter].identifier;
        //if ID == frame rate (as defined in unicap API) then return its current value
        if (charID == propertyName)
        {
          //check if the call succeeds 
          int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
          if( SUCCESS(returnValue) )
          {
            iris = listOfProperties[propertyCounter].value;
            return true;
          }
        }
      }
      //if property is not of type "range" go to the beginning of the loop
    }
  }
  // if property list was not obtained successfully or was not filled in before through 
  //the call to getListOfDeviceProperties, call the method 
  else if (getListOfDeviceProperties() == true)
  {
    if (listOfProperties.size() != 0)
    {
      for (int propertyCounter = 0; propertyCounter < deviceConfPropertyCounter; propertyCounter++)
      {
        if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
        {
          charID = listOfProperties[propertyCounter].identifier;
          if (charID == propertyName)
          {
            int returnValue = unicap_get_property( *handleCameraDevConf, &listOfProperties[propertyCounter]); // (3)
            if( SUCCESS(returnValue) )
            {
              iris = listOfProperties[propertyCounter].value;
              return true;
            }
          }
        }
        //if property is not of type "range" go to the beginning of the loop
      }
    }
    else
    {
      std::cout << "Property list is empty"<< std::endl;
      return false;
    }
  }
  // if neither of the above return error message
  else 
  {    
    std::cout << "Can not get property"<< std::endl;
    return false;
  }

}

bool CameraDeviceConfiguration::setVideoFrameRate(double &rate) {

  std::cout << "Inside CameraDeviceConfiguration setVideoFrameRate" << std::endl;

  return true;
}

bool CameraDeviceConfiguration::setVideoGammaValue(double &gamma) {

  std::cout << "Inside CameraDeviceConfiguration setVideoGammaValue" << std::endl;
  return true;
}

bool CameraDeviceConfiguration::setVideoSharpnessValue(double &sharpness) {

  std::cout << "Inside CameraDeviceConfiguration setVideoSharpnessValue" << std::endl;
  return true;
}

bool CameraDeviceConfiguration::setLensFocus(double &focus) {

  std::cout << "Inside CameraDeviceConfiguration setLensFocus" << std::endl;
  return true;
}

bool CameraDeviceConfiguration::setLensZoom(double &zoom) {
  std::cout << "Inside CameraDeviceConfiguration setLensZoom" << std::endl;
  return true;
}

bool CameraDeviceConfiguration::setLensIris(double &iris) {

  std::cout << "Inside CameraDeviceConfiguration setLensIris" << std::endl;
  return true;
}

