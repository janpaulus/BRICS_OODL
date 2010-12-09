#ifndef _MONOCULARCAMERAPROPERTYFACTORY_HPP_
#define _MONOCULARCAMERAPROPERTYFACTORY_HPP_

class MonocularCameraPropertyFactory
{
public:
    MonocularCameraPropertyFactory();
    createProperty(ColorPropertyDesc &propertySpecifier, MonocularCameraProperty &deviceProperty);
    ~MonocularCameraPropertyFactory();
};



#endif //~_MONOCULARCAMERAPROPERTYFACTORY_HPP_
