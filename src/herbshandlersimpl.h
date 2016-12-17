#ifndef HERBSHANDLERSIMPL_H
#define HERBSHANDLERSIMPL_H

#include <settings.h>
#include <hwiface.h>

class  HerbsHandlerSimpl : public IHerbsHandler, public IPolivControl
{
public:
    HerbsHandlerSimpl(HWiface * hardware,
                      ISettingsInt * settings);

    // IHerbsHandler interface
    void handleHerbs();

    // IDeviceModeSettings interface
    void setDeviceMode(DeviceMode);
    DeviceMode getDeviceMode() const;

    // IPolivControl interface
    DeviceStatus getDeviceStatus() const;
    HumidityVal getHumidity();

private:
    HWiface * hardware;
    ISettingsInt * settings;

    DeviceStatus status;
};

#endif // HERBSHANDLERSIMPL_H
