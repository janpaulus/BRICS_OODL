#include "ColorExposureConfiguration.hpp"


//Issue1:
//harmonizes possible property name combinations
//Like if white_u_balance, WhiteUBalance, White U Balance
// or brightness vs Brightness etc

//Issue2:
//Normalization of values for various camera properties
//can be done through  through access to "range" member attribute
//of unicap_property structure. "range" is a structure which holds
//min and max value for the given property

//Issue3:
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


ColorExposureConfiguration::ColorExposureConfiguration(): deviceColorExposureDev(NULL),
    handleColorExposureDev(NULL),
    returnStatus(STATUS_FAILURE),
    colorConfPropertyCounter(0)

{
    std::cout << "Creating ColorExposureConfiguration without arguments" << std::endl;
    hueValue.min = 0;
    hueValue.max = 0;
    saturationValue.min = 0;
    saturationValue.max = 0;
    whiteBalanceUValue.min = 0;
    whiteBalanceUValue.max = 0;
    whiteBalanceVValue.min = 0;
    whiteBalanceVValue.max = 0;
    brightnessValue.min = 0;
    brightnessValue.max = 0;
    gainControlValue.min = 0;
    gainControlValue.max = 0;
    shutterTime.min = 0;
    shutterTime.max = 0;
    exposureTime.min = 0;
    exposureTime.max = 0;
}


ColorExposureConfiguration::ColorExposureConfiguration(unicap_device_t *device, unicap_handle_t *handle): deviceColorExposureDev(device),
    handleColorExposureDev (handle),
    returnStatus(STATUS_FAILURE),
    colorConfPropertyCounter(0)
{
    std::cout << "Creating ColorExposureConfiguration with arguments" << std::endl;
    hueValue.min = 0;
    hueValue.max = 0;
    saturationValue.min = 0;
    saturationValue.max = 0;
    whiteBalanceUValue.min = 0;
    whiteBalanceUValue.max = 0;
    whiteBalanceVValue.min = 0;
    whiteBalanceVValue.max = 0;
    brightnessValue.min = 0;
    brightnessValue.max = 0;
    gainControlValue.min = 0;
    gainControlValue.max = 0;
    shutterTime.min = 0;
    shutterTime.max = 0;
    exposureTime.min = 0;
    exposureTime.max = 0;

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
    std::cout << "Inside ColorExposureConfiguration getListOfColorPropertiesVector" << std::endl;
    unicap_property_t tempProperty = {0};
    while(SUCCESS(unicap_enumerate_properties( *handleColorExposureDev, NULL, &tempProperty, colorConfPropertyCounter)))
    {

        listOfProperties.push_back(tempProperty);
        std::cout << 	listOfProperties.size()<< std::endl;
        std::cout << 	listOfProperties[colorConfPropertyCounter].identifier<<std::endl;
        colorConfPropertyCounter++;
        returnStatus = STATUS_SUCCESS;
    }

    if(listOfProperties.size() != 0)
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

bool ColorExposureConfiguration::unifyPropertyNames()
{
    //very dirty initializing vector with array of possible property names.
    listOfPropertytNames.push_back("brightness");
    listOfPropertytNames.push_back("Brightness");
    listOfPropertytNames.push_back("Contrast");
    listOfPropertytNames.push_back("contrast");
    listOfPropertytNames.push_back("hue");
    listOfPropertytNames.push_back("Hue");
    listOfPropertytNames.push_back("Shutter");
    listOfPropertytNames.push_back("shutter");
    listOfPropertytNames.push_back("Saturation");
    listOfPropertytNames.push_back("saturation");
    listOfPropertytNames.push_back("gain");
    listOfPropertytNames.push_back("Gain");
    listOfPropertytNames.push_back("Exposure");
    listOfPropertytNames.push_back("exposure");
    listOfPropertytNames.push_back("White Balance Temperature");
    if (listOfPropertytNames.size() != 0)
        return true;
    else
        return false;

}


bool ColorExposureConfiguration::normalizePropertyValues(double &userValue, unicap_property_t propertyToNormalize)
{
    //userValue range (0,1)
    if ((userValue < 0) || (userValue > 1))
    {
        std::cout << "Please enter values in the range [0,1]" << std::endl;
        return false;
    }
    else
    {
        double difference = propertyToNormalize.range.max - propertyToNormalize.range.min;
        userValue = propertyToNormalize.range.min+difference*userValue;
        return true;
    }

}


bool ColorExposureConfiguration::getHueValue(double &hue)
{
    std::cout << "Inside ColorExposureConfiguration getHueValue" << std::endl;
    const std::string propertyName1 ="hue";
    const std::string propertyName2 ="Hue";
    std::string charID;

    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
    {
        //camera properties returned by getListOfDeviceProperties

        for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
        {
            //check whether property of "range" type (defined in unicap API). hue value is of range type.
            //there are also menu, list, flag property types
            if(listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE )
            {
                //if range then check it for correct ID
                charID = listOfProperties[propertyCounter].identifier;

                //if ID == frame rate (as defined in unicap API) then return its current value
                if ((charID == propertyName1) || (charID == propertyName2))
                {
                    //check if the call succeeds
                    int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                    if( SUCCESS(returnValue) )
                    {

                        hue = listOfProperties[propertyCounter].value;
                        return true;
                    }
                }
            }
        }
    }
    // if property list was not obtained successfully or was not filled in before through
    //the call to getListOfDeviceProperties, call the method
    else if (getListOfColorProperties() == true)
    {
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE )
                {
                    charID = listOfProperties[propertyCounter].identifier;

                    if ((charID == propertyName1) || (charID == propertyName2))
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            hue = listOfProperties[propertyCounter].value;

                            return true;
                        }
                    }
                }
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
    const std::string propertyName1 ="contrast";
    const std::string propertyName2 ="Contrast";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                if( (charID == propertyName1) || (charID == propertyName2) )
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if ((charID == propertyName1) || (charID == propertyName2))
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
    const std::string propertyName1 ="saturation";
    const std::string propertyName2 ="Saturation";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if ((charID == propertyName1) || (charID == propertyName2))
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

// Need to fix white balance to include all the possible combinations of naming

bool ColorExposureConfiguration::getWhiteBalanceUValue(double &uValue)
{
    std::cout << "Inside ColorExposureConfiguration getWhiteBalanceUValue" << std::endl;
    const std::string propertyName ="white_balance_u";
    const std::string propertyName1 ="White Balance Temperature";
    const std::string propertyName2 ="white balance temperature";
    const std::string propertyName3 ="white_balance_temperature";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                if ((charID == propertyName) || (charID == propertyName1) || (charID == propertyName2) || (charID == propertyName3))
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if ((charID == propertyName) || (charID == propertyName1) || (charID == propertyName2) || (charID == propertyName3))
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
    const std::string propertyName1 ="White Balance Temperature";
    const std::string propertyName2 ="white balance temperature";
    const std::string propertyName3 ="white_balance_temperature";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                if ((charID == propertyName) || (charID == propertyName1) || (charID == propertyName2) || (charID == propertyName3))
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if ((charID == propertyName) || (charID == propertyName1) || (charID == propertyName2) || (charID == propertyName3))
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
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
        if (listOfProperties.size() != 0)
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
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
        if (listOfProperties.size() != 0)
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
    const std::string propertyName1 ="shutter";
    const std::string propertyName2 ="Shutter";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if ((charID == propertyName1) || (charID == propertyName2))
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



bool ColorExposureConfiguration::getExposureTime(double &eTime)
{
    std::cout << "Inside ColorExposureConfiguration getExposureTime" << std::endl;
    const std::string propertyName1 ="Exposure";
    const std::string propertyName2 ="exposure";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                        eTime = listOfProperties[propertyCounter].value;
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if ((charID == propertyName1) || (charID == propertyName2))
                    {
                        int returnValue = unicap_get_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                        if( SUCCESS(returnValue) )
                        {
                            eTime = listOfProperties[propertyCounter].value;
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


//Normalizer is introduced
//setting values through string matching
bool ColorExposureConfiguration::setHueValue(double &hue)
{
    std::cout << "Inside ColorExposureConfiguration setHueValue" << std::endl;
    char propertyName1[] ="hue";
    char propertyName2[] ="Hue";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                if ((charID == propertyName1))
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(hue, listOfProperties[propertyCounter]) == false)
                    {
                        hue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << hue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = hue;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, hue);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName2)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(hue, listOfProperties[propertyCounter]) == false)
                    {
                        hue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << hue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = hue;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, hue);
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName1)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(hue, listOfProperties[propertyCounter]) == false)
                        {
                            hue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << hue << std::endl;
                        }
                        listOfProperties[propertyCounter].value = hue;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1,hue);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName2)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(hue, listOfProperties[propertyCounter]) == false)
                        {
                            hue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << hue << std::endl;
                        }
                        charID = listOfProperties[propertyCounter].identifier;
                        if (charID == propertyName1)
                        {
                            listOfProperties[propertyCounter].value = hue;
                            int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                            if( SUCCESS(returnValue) )
                            {
                                std::cout << "Setting value is successful" << std::endl;
                                return true;
                            }
                            else
                            {
                                int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, hue);
                                if(SUCCESS(returnValue))
                                    return true;
                            }
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

//Normalizer is introduced
//setting values through string matching
bool ColorExposureConfiguration::setSaturationValue(double &saturation)
{

    std::cout << "Inside ColorExposureConfiguration setSaturation" << std::endl;
    char propertyName1[] ="saturation";
    char propertyName2[] ="Saturation";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                if ((charID == propertyName1))
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(saturation, listOfProperties[propertyCounter]) == false)
                    {
                        saturation = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << saturation << std::endl;
                    }

                    //set normalized value
                    listOfProperties[propertyCounter].value = saturation;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, saturation);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName2)
                {
                    if (normalizePropertyValues(saturation, listOfProperties[propertyCounter]) == false)
                    {
                        saturation = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << saturation << std::endl;
                    }
                    listOfProperties[propertyCounter].value = saturation;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, saturation);
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName1)
                    {
                        if (normalizePropertyValues(saturation, listOfProperties[propertyCounter]) == false)
                        {
                            saturation = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << saturation << std::endl;
                        }
                        listOfProperties[propertyCounter].value = saturation;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1,saturation);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName2)
                    {
                        charID = listOfProperties[propertyCounter].identifier;
                        if (charID == propertyName1)
                        {
                            if (normalizePropertyValues(saturation, listOfProperties[propertyCounter]) == false)
                            {
                                saturation = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                                std::cout << "Setting default value to " << saturation << std::endl;
                            }
                            listOfProperties[propertyCounter].value = saturation;
                            int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                            if( SUCCESS(returnValue) )
                            {
                                std::cout << "Setting value is successful" << std::endl;
                                return true;
                            }
                            else
                            {
                                int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, saturation);
                                if(SUCCESS(returnValue))
                                    return true;
                            }
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

//Normalizer is introduced
//setting values through string matching
bool ColorExposureConfiguration::setBrightnessValue(double &brightness)
{

    std::cout << "Inside ColorExposureConfiguration setBrightnessValue" << std::endl;
    char propertyName1[] ="brightness";
    char propertyName2[] ="Brightness";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                if (charID == propertyName1)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(brightness, listOfProperties[propertyCounter]) == false)
                    {
                        brightness = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << brightness << std::endl;
                    }
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
                else if (charID == propertyName2)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(brightness, listOfProperties[propertyCounter]) == false)
                    {
                        brightness = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << brightness << std::endl;
                    }

                    listOfProperties[propertyCounter].value = brightness;
                    //check if the call succeeds
                    unicap_set_property_manual(*handleColorExposureDev,propertyName2);
                    int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {

                        std::cout << "Setting value is successful" << std::endl;
                        return true;
                    }
                    else
                    {
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, brightness);
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName1)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(brightness, listOfProperties[propertyCounter]) == false)
                        {
                            brightness = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << brightness << std::endl;
                        }
                        listOfProperties[propertyCounter].value = brightness;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1,brightness);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else  if (charID == propertyName2)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(brightness, listOfProperties[propertyCounter]) == false)
                        {
                            brightness = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << brightness << std::endl;
                        }
                        listOfProperties[propertyCounter].value = brightness;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2,brightness);
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

//Normalizer is introduced
//setting values through string matching
bool ColorExposureConfiguration::setGainControlValue(double &gain)
{

    std::cout << "Inside ColorExposureConfiguration setGainControlValue" << std::endl;
    char propertyName1[] ="gain";
    char propertyName2[] ="Gain";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                if ((charID == propertyName1))
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(gain, listOfProperties[propertyCounter]) == false)
                    {
                        gain = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << gain << std::endl;
                    }
                    listOfProperties[propertyCounter].value = gain;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, gain);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName2)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(gain, listOfProperties[propertyCounter]) == false)
                    {
                        gain = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << gain << std::endl;
                    }
                    listOfProperties[propertyCounter].value = gain;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, gain);
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName1)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(gain, listOfProperties[propertyCounter]) == false)
                        {
                            gain = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << gain << std::endl;
                        }
                        listOfProperties[propertyCounter].value = gain;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1,gain);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName2)
                    {
                        charID = listOfProperties[propertyCounter].identifier;
                        if (charID == propertyName1)
                        {
                            //normalize user values to that of the camera
                            //Need to check the return value for the correctness
                            if (normalizePropertyValues(gain, listOfProperties[propertyCounter]) == false)
                            {
                                gain = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                                std::cout << "Setting default value to " << gain << std::endl;
                            }

                            listOfProperties[propertyCounter].value = gain;
                            int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                            if( SUCCESS(returnValue) )
                            {
                                std::cout << "Setting value is successful" << std::endl;
                                return true;
                            }
                            else
                            {
                                int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, gain);
                                if(SUCCESS(returnValue))
                                    return true;
                            }
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

//Normalizer is introduced
//setting values through string matching
bool ColorExposureConfiguration::setShutterTime(double &sTime)
{
    std::cout << "Inside ColorExposureConfiguration setShutterTime" << std::endl;
    char propertyName1[] ="Shutter";
    char propertyName2[] ="shutter";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                if ((charID == propertyName1))
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(sTime, listOfProperties[propertyCounter]) == false)
                    {
                        sTime = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << sTime << std::endl;
                    }
                    listOfProperties[propertyCounter].value = sTime;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, sTime);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName2)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(sTime, listOfProperties[propertyCounter]) == false)
                    {
                        sTime = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << sTime << std::endl;
                    }
                    listOfProperties[propertyCounter].value = sTime;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, sTime);
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName1)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(sTime, listOfProperties[propertyCounter]) == false)
                        {
                            sTime = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << sTime << std::endl;
                        }
                        listOfProperties[propertyCounter].value = sTime;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1,sTime);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName2)
                    {
                        charID = listOfProperties[propertyCounter].identifier;
                        if (charID == propertyName1)
                        {
                            //normalize user values to that of the camera
                            //Need to check the return value for the correctness
                            if (normalizePropertyValues(sTime, listOfProperties[propertyCounter]) == false)
                            {
                                sTime = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                                std::cout << "Setting default value to " << sTime << std::endl;
                            }
                            listOfProperties[propertyCounter].value = sTime;
                            int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                            if( SUCCESS(returnValue) )
                            {
                                std::cout << "Setting value is successful" << std::endl;
                                return true;
                            }
                            else
                            {
                                int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, sTime);
                                if(SUCCESS(returnValue))
                                    return true;
                            }
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

//Normalizer is introduced
//setting values through string matching
bool ColorExposureConfiguration::setExposureTime(double &eTime)
{
    std::cout << "Inside ColorExposureConfiguration setExposureTime" << std::endl;
    char propertyName1[] ="Exposure";
    char propertyName2[] ="exposure";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                if ((charID == propertyName1))
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(eTime, listOfProperties[propertyCounter]) == false)
                    {
                        eTime = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << eTime << std::endl;
                    }
                    listOfProperties[propertyCounter].value = eTime;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, eTime);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName2)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(eTime, listOfProperties[propertyCounter]) == false)
                    {
                        eTime = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << eTime << std::endl;
                    }
                    listOfProperties[propertyCounter].value = eTime;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, eTime);
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName1)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(eTime, listOfProperties[propertyCounter]) == false)
                        {
                            eTime = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << eTime << std::endl;
                        }
                        listOfProperties[propertyCounter].value = eTime;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1,eTime);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName2)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(eTime, listOfProperties[propertyCounter]) == false)
                        {
                            eTime = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << eTime << std::endl;
                        }
                        charID = listOfProperties[propertyCounter].identifier;
                        if (charID == propertyName1)
                        {
                            listOfProperties[propertyCounter].value = eTime;
                            int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                            if( SUCCESS(returnValue) )
                            {
                                std::cout << "Setting value is successful" << std::endl;
                                return true;
                            }
                            else
                            {
                                int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, eTime);
                                if(SUCCESS(returnValue))
                                    return true;
                            }
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

// The problem with this property is that it has AUTO mode which is often given as a separate property
//rather than mode. This complicates setting it to manual mode. Need to correct this.
//Normalizer is introduced
//setting values through string matching
bool ColorExposureConfiguration::setWhiteBalanceUValue(double &uValue)
{
    std::cout << "Inside ColorExposureConfiguration setWhiteBalanceVValue" << std::endl;
    char propertyName[] ="white_balance_u";
    char propertyName1[] ="White Balance Temperature";
    char propertyName2[] ="white balance temperature";
    char propertyName3[] ="white_balance_temperature";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(uValue, listOfProperties[propertyCounter]) == false)
                    {
                        uValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << uValue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = uValue;
                    //check if the call succeeds
                    unicap_set_property_manual(*handleColorExposureDev,propertyName);
                    int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {

                        std::cout << "Setting value is successful" << std::endl;
                        return true;
                    }
                    else
                    {
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName, uValue);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName1)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(uValue, listOfProperties[propertyCounter]) == false)
                    {
                        uValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << uValue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = uValue;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, uValue);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName2)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(uValue, listOfProperties[propertyCounter]) == false)
                    {
                        uValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << uValue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = uValue;
                    //check if the call succeeds
                    unicap_set_property_manual(*handleColorExposureDev,propertyName2);
                    int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {

                        std::cout << "Setting value is successful" << std::endl;
                        return true;
                    }
                    else
                    {
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, uValue);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName3)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(uValue, listOfProperties[propertyCounter]) == false)
                    {
                        uValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << uValue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = uValue;
                    //check if the call succeeds
                    unicap_set_property_manual(*handleColorExposureDev,propertyName3);
                    int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {

                        std::cout << "Setting value is successful" << std::endl;
                        return true;
                    }
                    else
                    {
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName3, uValue);
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(uValue, listOfProperties[propertyCounter]) == false)
                        {
                            uValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << uValue << std::endl;
                        }
                        listOfProperties[propertyCounter].value = uValue;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName, uValue);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName1)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(uValue, listOfProperties[propertyCounter]) == false)
                        {
                            uValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << uValue << std::endl;
                        }
                        listOfProperties[propertyCounter].value = uValue;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, uValue);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName2)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(uValue, listOfProperties[propertyCounter]) == false)
                        {
                            uValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << uValue << std::endl;
                        }
                        listOfProperties[propertyCounter].value = uValue;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, uValue);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName3)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(uValue, listOfProperties[propertyCounter]) == false)
                        {
                            uValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << uValue << std::endl;
                        }
                        listOfProperties[propertyCounter].value = uValue;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName3, uValue);
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

// The problem with this property is that it has AUTO mode which is often given as a separate property
//rather than mode. This complicates setting it to manual mode. Need to correct this.
//Normalizer is introduced
//setting values through string matching
bool ColorExposureConfiguration::setWhiteBalanceVValue(double &vValue)
{
    std::cout << "Inside ColorExposureConfiguration setWhiteBalanceVValue" << std::endl;
    char propertyName[] ="white_balance_v";
    char propertyName1[] ="White Balance Temperature";
    char propertyName2[] ="white balance temperature";
    char propertyName3[] ="white_balance_temperature";
    std::string charID;

    //check whether listOfProperties was filled in successfully and not empty
    if (SUCCESS(returnStatus) && (listOfProperties.size() != 0))
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
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(vValue, listOfProperties[propertyCounter]) == false)
                    {
                        vValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << vValue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = vValue;
                    //check if the call succeeds
                    unicap_set_property_manual(*handleColorExposureDev,propertyName);
                    int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {

                        std::cout << "Setting value is successful" << std::endl;
                        return true;
                    }
                    else
                    {
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName, vValue);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName1)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(vValue, listOfProperties[propertyCounter]) == false)
                    {
                        vValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << vValue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = vValue;
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
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, vValue);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName2)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(vValue, listOfProperties[propertyCounter]) == false)
                    {
                        vValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << vValue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = vValue;
                    //check if the call succeeds
                    unicap_set_property_manual(*handleColorExposureDev,propertyName2);
                    int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {

                        std::cout << "Setting value is successful" << std::endl;
                        return true;
                    }
                    else
                    {
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, vValue);
                        if(SUCCESS(returnValue))
                            return true;
                    }
                }
                else if (charID == propertyName3)
                {
                    //normalize user values to that of the camera
                    //Need to check the return value for the correctness
                    if (normalizePropertyValues(vValue, listOfProperties[propertyCounter]) == false)
                    {
                        vValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                        std::cout << "Setting default value to " << vValue << std::endl;
                    }
                    listOfProperties[propertyCounter].value = vValue;
                    //check if the call succeeds
                    unicap_set_property_manual(*handleColorExposureDev,propertyName3);
                    int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]); // (3)
                    if( SUCCESS(returnValue) )
                    {

                        std::cout << "Setting value is successful" << std::endl;
                        return true;
                    }
                    else
                    {
                        int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName3, vValue);
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
        if (listOfProperties.size() != 0)
        {
            for (int propertyCounter = 0; propertyCounter < colorConfPropertyCounter; propertyCounter++)
            {
                if( listOfProperties[propertyCounter].type == UNICAP_PROPERTY_TYPE_RANGE ) // (2)
                {
                    charID = listOfProperties[propertyCounter].identifier;
                    if (charID == propertyName)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(vValue, listOfProperties[propertyCounter]) == false)
                        {
                            vValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << vValue << std::endl;
                        }
                        listOfProperties[propertyCounter].value = vValue;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName, vValue);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName1)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(vValue, listOfProperties[propertyCounter]) == false)
                        {
                            vValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << vValue << std::endl;
                        }
                        listOfProperties[propertyCounter].value = vValue;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName1, vValue);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName2)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(vValue, listOfProperties[propertyCounter]) == false)
                        {
                            vValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << vValue << std::endl;
                        }
                        listOfProperties[propertyCounter].value = vValue;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName2, vValue);
                            if(SUCCESS(returnValue))
                                return true;
                        }

                    }
                    else if (charID == propertyName3)
                    {
                        //normalize user values to that of the camera
                        //Need to check the return value for the correctness
                        if (normalizePropertyValues(vValue, listOfProperties[propertyCounter]) == false)
                        {
                            vValue = listOfProperties[propertyCounter].range.max/2.0 ;//set as default half of the maximum
                            std::cout << "Setting default value to " << vValue << std::endl;
                        }
                        listOfProperties[propertyCounter].value = vValue;
                        int returnValue = unicap_set_property( *handleColorExposureDev, &listOfProperties[propertyCounter]);
                        if( SUCCESS(returnValue) )
                        {
                            std::cout << "Setting value is successful" << std::endl;
                            return true;
                        }
                        else
                        {
                            int returnValue = unicap_set_property_value(*handleColorExposureDev,propertyName3, vValue);
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

