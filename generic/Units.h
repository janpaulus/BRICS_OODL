/* 
 * File:   Units.h
 * Author: jan
 *
 * Created on September 1, 2010, 5:36 PM
 */

#ifndef UNITS_H
#define	UNITS_H
#include <boost/units/pow.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/prefixes.hpp>


using namespace boost::units;
using namespace boost::units::si;
using namespace boost::units::angle;

typedef boost::units::make_scaled_unit<si::length, boost::units::scale<10, boost::units::static_rational<-3> > >::type millimeter;
typedef boost::units::make_scaled_unit<si::time, boost::units::scale<10, boost::units::static_rational<-3> > >::type millisecond;
//BOOST_UNITS_STATIC_CONSTANT(millimeters, millimeter);

#endif	/* UNITS_H */

