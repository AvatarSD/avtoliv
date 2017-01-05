/*
 * by S.D.
 * avatarsd.com
 */

/* I2C Memory Map
 * __________________HEADER_____________________
 * |__START__|__SIZE__|_DESCRIPTIONS_|_OPTIONS_|
 * |0        |16      |guid          |ro       |
 * |16       |1       |i2c addr      |ro       |
 * |17       |2       |require temp  |rw       |
 * |19       |1       |sensors count |ro       |
 * |20       |2       |[res]stat&ctl |rw       |
 * ---------------------------------------------
 * |SIZE: 22 |
 *
 * ________________Device Node__________________
 * |__START__|__SIZE__|_DESCRIPTIONS_|_OPTIONS_|
 * |0        |8       |ROM           |ro       |
 * |8        |2       |Temp          |ro       |
 * |10       |1       |[res]stat&ctl |rw       |
 * ---------------------------------------------
 * |SIZE: 11 |
 *
 * ___________________Main__________________
 * |__START__|__SIZE__|____DESCRIPTIONS____|
 * |0        |21      |HEADER              |
 * |22       |13      |[res]               |
 * |35+N     |46+N    |Nodes(N={0..19})    |
 * -----------------------------------------
 * |SIZE:256 |
 *
 */


#include "mappedmemory.h"
#include <settings.h>
#include <slaveaddres.h>

ISettingsExt * settings = nullptr; /* settings in eeprom */
IPolivControl * control = nullptr;       /* main poliv iface   */
ITwiSlave * network = nullptr;          /* server pointer to
                                         change address     */


//static_assert(sizeof(MainMem) == 256, "MainMen is not 256bytes in size");

//typedef MainMem MemoryMammer;
//MappedMemory::MappedMemory(ISettingsExt * settngs,
//                           IPolivControl * contrl,
//                           ITwiSlave * net)
//{
//    settings = settngs;
//    control = contrl;
//    network = net;
//    SlaveAddress::setISlaveAddress(net);
//}
//int8_t MappedMemory::write(uint8_t addr, uint8_t data)
//{
//    return MemoryMammer::write(addr, data);
//}
//int16_t MappedMemory::read(uint8_t addr)
//{
//    return MemoryMammer::read(addr);
//}
//uint16_t MappedMemory::mapsize()
//{
//    return sizeof(MemoryMammer);
//}
