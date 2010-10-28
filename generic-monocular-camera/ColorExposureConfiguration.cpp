#include "ColorExposureConfiguration.hpp"




ColorExposureConfiguration::ColorExposureConfiguration(): deviceColorExposureDev(NULL), handleColorExposureDev(NULL),
                                                          colorConfPropertyCounter(0), returnStatus(STATUS_FAILURE)
{
    std::cout << "Creating ColorExposureConfiguration without arguments" << std::endl;

}


ColorExposureConfiguration::ColorExposureConfiguration(unicap_device_t *device, unicap_handle_t *handle): deviceColorExposureDev(device),
                                                                                                          handleColorExposureDev (handle),
                                                                                                          colorConfPropertyCounter(0),
                                                                                                          returnStatus(STATUS_FAILURE)
{
    std::cout << "Creating ColorExposureConfiguration with arguments" << std::endl;

}


ColorExposureConfiguration::ColorExposureConfiguration(ColorExposureConfiguration &colorconfig)
{


}

ColorExposureConfiguration& ColorExposureConfiguration::operator=(ColorExposureConfiguration &colorconfig)
{
    if(&colorconfig != this)
    {
        std::cout << "Inside ColorExposureConfiguration assignment" <<std::endl;
    }

    return *this;
}


ColorExposureConfiguration::~ColorExposureConfiguration() 
{
    std::cout << "Destroying ColorExposureConfiguration with arguments" << std::endl;

}


bool ColorExposureConfiguration::getListOfColorProperties() 
{
    std::cout << "Inside ColorExposureConfiguration getListOfColorProperties" << std::endl;
    int returnValue = 0;
    //number of properties allocated is 30 for now, change it to const or make it dynamic
    for( int propertyCounter = 0; propertyCounter < 30 ; propertyCounter++ ) 
    {
        returnValue = unicap_enumerate_properties( *handleColorExposureDev, NULL, &listOfProperties[propertyCounter], 
                                                   propertyCounter);
        if( SUCCESS(returnValue) )
        {
            std::cout << listOfProperties[propertyCounter].identifier<<std::endl;
            colorConfPropertyCounter++;
            returnStatus = STATUS_SUCCESS;
        }
        else
            break;

    }

    if(listOfProperties != NULL )
    {
        std::cout << "Number of properties " << colorConfPropertyCounter<<std::endl;
        return true;
    }
    else
    {
        std::cout << "Property list is empty"<<std::endl;
        return false;
    }
 
}


//harmonizes possible property name combinations
//Like if white_u_balance, WhiteUBalance, White U Balance
// or brightness vs Brightness etc 
bool ColorExposureConfiguration::unifyPropertyNames()
{



}


bool ColorExposureConfiguration::getHueValue(double &hue) 
{
    std::cout << "Inside ColorExposureConfiguration getHueValue" << std::endl;
    const std::string propertyName ="hue";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
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
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        hue = listOfProperties[propertyCounter].value;
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
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            hue = listOfProperties[propertyCounter].value;
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
}


bool ColorExposureConfiguration::getContrastValue(double &contrast) 
{
   std::cout << "Inside ColorExposureConfiguration getContrastValue" << std::endl;
    const std::string propertyName ="contrast";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
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
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        contrast = listOfProperties[propertyCounter].value;
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
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            contrast = listOfProperties[propertyCounter].value;
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
}


bool ColorExposureConfiguration::getSaturationValue(double &saturation) 
{
   std::cout << "Inside ColorExposureConfiguration getSaturationValue" << std::endl;
    const std::string propertyName ="saturation";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
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
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        saturation = listOfProperties[propertyCounter].value;
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
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            saturation = listOfProperties[propertyCounter].value;
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
}


bool ColorExposureConfiguration::getWhiteBalanceUValue(double &uValue) 
{
   std::cout << "Inside ColorExposureConfiguration getWhiteBalanceUValue" << std::endl;
    const std::string propertyName ="white_balance_u";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
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
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        uValue = listOfProperties[propertyCounter].value;
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
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            uValue = listOfProperties[propertyCounter].value;
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
}


bool ColorExposureConfiguration::getWhiteBalanceVValue(double &vValue) 
{
   std::cout << "Inside ColorExposureConfiguration getWhiteBalanceVValue" << std::endl;
    const std::string propertyName ="white_balance_v";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
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
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        vValue = listOfProperties[propertyCounter].value;
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
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            vValue = listOfProperties[propertyCounter].value;
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
}


//TEMPORARY SOLUTION FOR CAPITAL AND LOWERCASE LETTERS
//NEED TO SOLVE THIS CLEVERLY

bool ColorExposureConfiguration::getBrightnessValue(double &brightness) 
{
   std::cout << "Inside ColorExposureConfiguration getBrightnessValue" << std::endl;
   const std::string propertyName1 ="brightness";
   const std::string propertyName2 = "Brightness";

    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if ((charID == propertyName1) || (charID == propertyName2))
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        brightness = listOfProperties[propertyCounter].value;
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
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if((charID == propertyName1) || (charID == propertyName2))
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            brightness = listOfProperties[propertyCounter].value;
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
}


bool ColorExposureConfiguration::getGainControlValue(double &gain) 
{
   std::cout << "Inside ColorExposureConfiguration getGainControlValue" << std::endl;
    const std::string propertyName1 ="gain";
    const std::string propertyName2 ="Gain";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if ((charID == propertyName1)||(charID == propertyName2))
                {
                    //check if the call succeeds 
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        gain = listOfProperties[propertyCounter].value;
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
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if ((charID == propertyName1)||(charID == propertyName2))
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            gain = listOfProperties[propertyCounter].value;
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
}



bool ColorExposureConfiguration::getShutterTime(double &sTime) 
{
   std::cout << "Inside ColorExposureConfiguration getShutterTime" << std::endl;
    const std::string propertyName ="shutter";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
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
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        sTime = listOfProperties[propertyCounter].value;
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
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            sTime = listOfProperties[propertyCounter].value;
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
}



bool ColorExposureConfiguration::getExposureTime(double &eTime) {

}


bool ColorExposureConfiguration::getColorTemperatureValue(double &temp) 
{
   std::cout << "Inside ColorExposureConfiguration getColorTemperatureValue" << std::endl;
    const std::string propertyName ="temperature";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
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
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {
                        temp = listOfProperties[propertyCounter].value;
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
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            temp = listOfProperties[propertyCounter].value;
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
}



// Maybe instead of having just an array for the name of the existing list of device properties
//We should introduce an array of tuples/pairs for (property.id, property.value)
//This way we can obtain proverty values in one call and save them
// and for setting properties values one would have to write to the array of tuples
// then the value from the respective tuple would be written to device itself.
// This way the calls might look like "stateful", otherwise if the call to a device
// does not succeed the value we wanted to set/get might just disappear.
//So, one needs to find a trade-off for this design. Now it is "stateless"
// Maybe for a device it is a good decision to have stateless though, it does not want
// to bother itself with unsuccessful clients.

bool ColorExposureConfiguration::setHueValue(double &hue) {

}

bool ColorExposureConfiguration::setChromaValue(double &chroma) {

}

bool ColorExposureConfiguration::setSaturationValue(double &saturation) {

}


bool ColorExposureConfiguration::setWhiteBalanceUValue(double &uValue) {

}

bool ColorExposureConfiguration::setWhiteBalanceVValue(double &vValue) {

}


//Temporary solution for capital and lowercase letters
//Need to solve this cleverly
bool ColorExposureConfiguration::setBrightnessValue(double &brightness) {

  std::cout << "Inside ColorExposureConfiguration setBrightnessValue" << std::endl;
    char propertyName1[] ="brightness";
    char propertyName2[] ="Brightness";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if ((charID == propertyName1) || (charID == propertyName2))
                {
                  listOfProperties[propertyCounter].value = brightness;
                  //check if the call succeeds 
                   unicap_set_property_manual(*handleColorExposureDev,propertyName1);
                  int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                  if( SUCCESS(returnValue) )
                  {
                   
                    std::cout << "Setting value is successful" << std::endl;
                    return true;
                  }
                  else
                  {
                    int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, brightness);                   
                    if(SUCCESS(returnValue))
                      return true;
                  }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if ((charID == propertyName1) || (charID == propertyName2))
                    {
                      listOfProperties[propertyCounter].value = brightness;
                      int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); 
                        if( SUCCESS(returnValue) )
                        {
                          std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                          int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, brightness);
                          if(SUCCESS(returnValue))
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

}


bool ColorExposureConfiguration::setGainControlValue(double &gain)
{

  std::cout << "Inside ColorExposureConfiguration setGainControlValue" << std::endl;
  char propertyName[] = "gain";

  std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties != NULL))
    {
        //here member variable deviceConfProperty is a total number of 
        //camera properties returned by getListOfDeviceProperties
        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). Frame rate is of range type.
            //there are also menu, list, flag property types
            if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;
                //if ID == frame rate (as defined in unicap API) then return its current value
                if(charID == propertyName)
                {
                  listOfProperties[propertyCounter].value = gain;
                  //check if the call succeeds 
                  unicap_set_property_manual(*handleColorExposureDev,propertyName);
                  int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); 
                  if( SUCCESS(returnValue) )
                  {
                   
                    std::cout << "Setting value is successful" << std::endl;
                    return true;
                  }
                  else
                  {
                    int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName, gain);                
                    if(SUCCESS(returnValue))
                      return true;
                  }
                }
            }
            //if property is not of type "range" go to the beginning of the loop
        }
    }
    // if property list was not obtained successfully or was not filled in before through 
    //the call to getListOfDeviceProperties, call the method 
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties != NULL)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                      listOfProperties[propertyCounter].value = gain;
                      int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                          std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                          int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName, gain);
                          if(SUCCESS(returnValue))
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

}


bool ColorExposureConfiguration::setShutterTime(double &sTime) {

}

bool ColorExposureConfiguration::setExposureTime(double &eTime) {

}

bool ColorExposureConfiguration::setColorTemperatureValue(double &temp) {

}

