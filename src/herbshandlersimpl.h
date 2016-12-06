#ifndef HERBSHANDLERSIMPL_H
#define HERBSHANDLERSIMPL_H

#include <settings.h>
#include <hwiface.h>

class HerbsHandlerSimpl : public IHerbsHandler, public IPolivControl
{
public:

    HerbsHandlerSimpl(HWiface * hardware,
                      IPolivSettingsInt * settings);


    // IHerbsHandler interface
    void handleHerbs();
    // IPolivControl interface
    void setMode();


private:
    HWiface * hdware;
    IPolivSettingsInt * stngs;
};

#endif // HERBSHANDLERSIMPL_H