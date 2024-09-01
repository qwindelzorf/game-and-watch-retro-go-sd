#include <odroid_system.h>

#include "main.h"
#include "gui.h"
#include "rg_i18n.h"
#include "ff.h"

void handle_save_manager_menu()
{
    FATFS FatFs;  // Fatfs handle
    FIL fil;      // File handle
    FRESULT fres; // Result after operations

    fres = f_mount(&FatFs, (const TCHAR *)"", 1); // 1=mount now
    if (fres != FR_OK)
    {
        printf("f_mount error (%i)\r\n", fres);
        while (1);
    }

    fres = f_open(&fil, (const TCHAR *)"test.txt", FA_READ);
    if (fres != FR_OK)
    {
        printf("f_open error (%i)\r\n", fres);
        while (1);
    }
    BYTE readBuf[30];
    UINT read;
    // FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);
    fres = f_read(&fil, (void *)readBuf, 30, &read);
    if (fres != FR_OK)
    {
        printf("Read string from 'test.txt' contents: %s\r\n", readBuf);
    }
    else
    {
        printf("f_gets error (%i)\r\n", fres);
    }

    f_close(&fil);

    //We're done, so de-mount the drive
    f_mount(NULL, (const TCHAR *)"", 0);
}
