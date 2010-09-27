/*!
 * \file SickS300Message.hh
 * \brief Definition of class SickS300Message.
 *
 * Code by Jason C. Derenick and Thomas H. Miller.
 * Contact derenick(at)lehigh(dot)edu
 *
 * The Sick LIDAR Matlab/C++ Toolbox
 * Copyright (c) 2008, Jason C. Derenick and Thomas H. Miller
 * All rights reserved.
 *
 * This software is released under a BSD Open-Source License.
 * See http://sicktoolbox.sourceforge.net
 */

#ifndef SICK_S300_MESSAGE_HH
#define SICK_S300_MESSAGE_HH

/* Definition dependencies */
#include <string.h>
#include <netinet/in.h>   
#include "SickMessage.h"
#include "SickException.h"

#define CRC16_GEN_POL 0x8005                        ///< Used to compute CRCs

/** Makes a "short" in little endian */
#define MKSHORT(a,b) ((unsigned short) (a) | ((unsigned short)(b) << 8))

#define SICK_S300_MSG_HEADER_LEN            (4)  ///< Sick S300 message length in bytes
#define SICK_S300_MSG_PAYLOAD_MAX_LEN     (812)  ///< Sick S300 max payload length in bytes
#define SICK_S300_MSG_TRAILER_LEN           (2)  ///< Sick S300 message trailer length in bytes 

/* Associate the namespace */
namespace SickToolbox {

  /**
   * \brief A class to represent all messages sent to and from the Sick S300
   *
   * This class helps to construct messages to be sent to the Sick. It also
   * provides a container for received messages to be parsed into.
   */
  class SickS300Message : public SickMessage< SICK_S300_MSG_HEADER_LEN, SICK_S300_MSG_PAYLOAD_MAX_LEN, SICK_S300_MSG_TRAILER_LEN >
  {

  public:
  
    /** Default constructor. Constructs an empty message (not well-formed!). */
    SickS300Message( );

    /** Constructs a frame by using BuildMessage(). */
    SickS300Message( const uint8_t dest_address, const uint8_t * const payload_buffer, const unsigned int payload_length );

    /** Constructs a frame using ParseMessage(). */
    SickS300Message( uint8_t * const message_buffer );

    /** Constructs a well-formed raw frame from input fields. */
    void BuildMessage( uint8_t dest_address, const uint8_t * const payload_buffer,
		       const unsigned int payload_length );
    
    /** Populates fields from a (well-formed) raw frame. */
    void ParseMessage( const uint8_t * const message_buffer );

    /** Gets the address of the frame. */
    uint8_t GetDestAddress( ) const { return _message_buffer[1]; }

    /** Gets the command code associated with the message */
    uint8_t GetCommandCode( ) const { return _message_buffer[MESSAGE_HEADER_LENGTH]; }

    /** Gets the status byte from an S300 response message (NOTE: only applies to Sick S300 response telegrams!) */
    uint8_t GetStatusByte( ) const { return _message_buffer[MESSAGE_HEADER_LENGTH+_payload_length-1]; }
    
    /** Gets the checksum for the message. */
    uint16_t GetChecksum( ) const { return _checksum; }
    
    /** Reset the data associated with this message (for initialization purposes) */
    void Clear( );
    
    /** A debugging function that prints the contents of the message. */
    void Print( ) const;

    /** Destructor */
    ~SickS300Message();

  protected:

    /** The checksum (CRC16) */
    uint16_t _checksum;
    
  private:

    /** Computes the checksum of the frame. */
    uint16_t _computeCRC( uint8_t * data, unsigned int data_length ) const;

  };

} /* namespace SickToolbox */
  
#endif //SICK_S300_MESSAGE_HH
