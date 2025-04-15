#include "cbase.h"
#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>

enum BrowserType {
    BROWSER_UNKNOWN,
    BROWSER_CHROME,
    BROWSER_FIREFOX,
    BROWSER_EDGE
};

BrowserType detect_browser() {
    return (BrowserType)EM_ASM_INT({
        let ua = navigator.userAgent.toLowerCase();
        if (ua.includes('edg')) return 3;
        if (ua.includes('chrome')) return 1;
        if (ua.includes('firefox')) return 2;
        return 0;
    });
}

int main() {
    BrowserType browser = detect_browser();

    switch (browser) {
        case BROWSER_CHROME:
            Msg("Running in Chrome\n");
            break;
        case BROWSER_FIREFOX:
            Msg("Running in Firefox\n");
            break;
        case BROWSER_EDGE:
            Msg("Error: Microsoft Edge is not supported\n");
            #error
            break;
        default:
            Msg("Unknown browser\n");
            break;
    }
    return 0;
}
