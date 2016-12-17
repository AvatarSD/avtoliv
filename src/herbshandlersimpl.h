#ifndef HERBSHANDLERSIMPL_H
#define HERBSHANDLERSIMPL_H

#include <settings.h>
#include <hwiface.h>

class  HerbsHandlerSimpl : public IHerbsHandler, public IPolivControl
{
public:
    HerbsHandlerSimpl(HWiface * hardware,
                      IPolivSettingsInt * settings);

    // IHerbsHandler interface
    void handleHerbs();

    // IPolivControl interface
    void setMode(DeviceMode);
    DeviceMode getPolivMode();
    DeviceStatus getStatus();
    uint16_t getHumidity(uint8_t);

private:
    HWiface * hdware;
    IPolivSettingsInt * stngs;
    DeviceStatus stage;

};

#endif // HERBSHANDLERSIMPL_H
