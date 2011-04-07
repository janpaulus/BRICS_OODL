#ifndef _MONOCULARCAMERAPROPERTYFACTORY_HPP_
#define _MONOCULARCAMERAPROPERTYFACTORY_HPP_

class MonocularCameraPropertyFactory
{
public:
    MonocularCameraPropertyFactory();
    virtual bool createProperty(PropertyDescriptor &propertySpecifier, MonocularCameraProperty &deviceProperty) = 0;
    virtual ~MonocularCameraPropertyFactory();
};

class MonocularCameraRangePropertyFactory : public MonocularCameraPropertyFactory
{
    public:
    MonocularCameraRangePropertyFactory();
    bool createProperty(PropertyDescriptor &propertySpecifier, MonocularCameraProperty &deviceProperty);
    virtual ~MonocularCameraRangePropertyFactory();

};

#endif //~_MONOCULARCAMERAPROPERTYFACTORY_HPP_
