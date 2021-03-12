#ifndef _XMMS_CHARSET_H
#define _XMMS_CHARSET_H

typedef enum xmms_rcc_class_t {
    XMMS_RCC_ID3 = 0,
    XMMS_RCC_ID3V2,
    XMMS_RCC_PL,
    XMMS_RCC_PLFS,
    XMMS_RCC_FS,
    XMMS_RCC_OUT,
    XMMS_RCC_CTYPE,
    XMMS_RCC_UTF8
} xmms_rcc_class;

void xmms_rcc_init();
void xmms_rcc_free();
void xmms_rcc_prefswin_create(void *prefswin_notebook);
void xmms_rcc_prefswin_apply();

char *xmms_rcc_fs2pl(const char *fnstring, const char *filename);
char *xmms_rcc_get(xmms_rcc_class charset, const char *buf);
char *xmms_rcc_put(xmms_rcc_class charset, const char *buf);
char *xmms_rcc_sized_put(xmms_rcc_class charset, const char *buf, int size);
char *xmms_rcc_recode(xmms_rcc_class from, xmms_rcc_class to, const char *buf);
char *xmms_rcc_sized_recode(xmms_rcc_class from, xmms_rcc_class to, const char *buf, int size);
char *xmms_rcc_fs(xmms_rcc_class from, xmms_rcc_class to, const char *fspath, const char *path, const char *filename);

const char *xmms_rcc_string(const char *buf);
const char *xmms_rcc_get_language();
int xmms_rcc_get_id3v2_encoding();

#endif /* _XMMS_CHARSET_H */
