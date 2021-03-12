#include <stdio.h>
#include <string.h>

#include <gtk/gtklabel.h>
#include <gtk/gtknotebook.h>

#include "config.h"
#ifdef HAVE_LIBRCC_H
# ifdef HAVE_LIBRCCUI_H
#  define HAVE_LIBRCC
#  include <librcc.h>
#  include <librccui.h>
# endif /* HAVE_LIBRCCUI_H */
#endif /* HAVE_LIBRCC_H */

#include "rcc.h"
#include "rcc_langs.h"

#ifdef HAVE_LIBRCC
static rcc_context ctx = NULL;
static rcc_ui_context uictx = NULL;

static rcc_class_default_charset default_id3[] = {
    { "ru", "CP1251" },
    { NULL, NULL }
};

static rcc_class classes[] = {
    { "id3", RCC_CLASS_STANDARD, NULL, default_id3, "ID3 Encoding", 0 },
    { "id3v2", RCC_CLASS_STANDARD, "id3", default_id3, "ID3 v.2 Encoding", 0 },
    { "pl", RCC_CLASS_STANDARD, "id3", default_id3, "PlayList Title Encoding", 0 },
    { "plfs", RCC_CLASS_STANDARD, "pl", NULL, "PlayList File Encoding", 0 },
    { "fs", RCC_CLASS_FS, "LC_CTYPE", NULL, "FileSystem Encoding", 0 },
    { "out", RCC_CLASS_TRANSLATE_LOCALE, "LC_CTYPE", NULL, NULL, 0 },
    { "ctype", RCC_CLASS_STANDARD, "LC_CTYPE", NULL, NULL, RCC_CLASS_FLAG_CONST|RCC_CLASS_FLAG_SKIP_SAVELOAD },
    { "utf8", RCC_CLASS_STANDARD, "UTF-8", NULL, NULL, RCC_CLASS_FLAG_CONST|RCC_CLASS_FLAG_SKIP_SAVELOAD },
    { NULL }
};
#endif /* HAVE_LIBRCC */



void xmms_rcc_init() {
#ifdef HAVE_LIBRCC
    rccInit();
    rccUiInit();
    ctx = rccCreateContext(NULL, 0, 0, classes, 0);
    rccInitDb4(ctx, NULL, 0);
    rccLoad(ctx, "xmms");
    uictx = rccUiCreateContext(ctx);
#endif /* HAVE_LIBRCC */
}

void xmms_rcc_free() {
#ifdef HAVE_LIBRCC
    rccUiFreeContext(uictx);
    rccSave(ctx, "xmms");
    rccFreeContext(ctx);
    rccUiFree();
    rccFree();
#endif /* HAVE_LIBRCC */
}

void xmms_rcc_prefswin_create(void *prefswin_notebook) {
#ifdef HAVE_LIBRCC
    GtkWidget *vbox;
    vbox = (GtkWidget*)rccUiGetPage(uictx, NULL);
    gtk_notebook_append_page(GTK_NOTEBOOK(prefswin_notebook), vbox, gtk_label_new(rccUiGetDefaultPageName()->title));
#endif /* HAVE_LIBRCC */
}

void xmms_rcc_prefswin_apply() {
#ifdef HAVE_LIBRCC
    rccUiUpdate(uictx);
    rccSave(ctx, "xmms");
#endif /* HAVE_LIBRCC */
}

char *xmms_rcc_fs2pl(const char *fnstring, const char *filename) {
#ifdef HAVE_LIBRCC
    rcc_language_config config;

    if (!rccStringCheck(fnstring)) return NULL;

    config = rccGetConfig(ctx, rccStringGetLanguage(fnstring));
    if (!config) return NULL;

    if (rccConfigGetCurrentCharset(config, (rcc_class_id)XMMS_RCC_FS) == rccConfigGetCurrentCharset(config, (rcc_class_id)XMMS_RCC_PLFS))
	return NULL;
#endif /* HAVE_LIBRCC */
    
    return xmms_rcc_get(XMMS_RCC_PLFS, fnstring);
}


/* rcc_string to out */
char *xmms_rcc_get(xmms_rcc_class charset, const char *buf) {
#ifdef HAVE_LIBRCC
    return (char*)rccTo(ctx, (rcc_class_id)charset, (const rcc_string)buf);
#else /* HAVE_LIBRCC */
    return NULL;
#endif /* HAVE_LIBRCC */
}

char *xmms_rcc_put(xmms_rcc_class charset, const char *buf) {
#ifdef HAVE_LIBRCC
    return (char*)rccFrom(ctx, (rcc_class_id)charset, buf);
#else /* HAVE_LIBRCC */
    return NULL;
#endif /* HAVE_LIBRCC */
}

char *xmms_rcc_sized_put(xmms_rcc_class charset, const char *buf, int size) {
#ifdef HAVE_LIBRCC
    return (char*)rccSizedFrom(ctx, (rcc_class_id)charset, buf, size);
#else /* HAVE_LIBRCC */
    return NULL;
#endif /* HAVE_LIBRCC */
}

char *xmms_rcc_recode(xmms_rcc_class from, xmms_rcc_class to, const char *buf) {
#ifdef HAVE_LIBRCC
    if (((from==XMMS_RCC_CTYPE)&&(to==XMMS_RCC_OUT))||((from==XMMS_RCC_OUT)&&(to==XMMS_RCC_CTYPE))) {
	if (!rccGetSelectedCharset(ctx, XMMS_RCC_OUT)) return NULL;
    }

    return (char*)rccRecode(ctx, (rcc_class_id)from, (rcc_class_id)to, buf);
#else /* HAVE_LIBRCC */
    return NULL;
#endif /* HAVE_LIBRCC */
}

char *xmms_rcc_sized_recode(xmms_rcc_class from, xmms_rcc_class to, const char *buf, int size) {
#ifdef HAVE_LIBRCC
    return (char*)rccSizedRecode(ctx, (rcc_class_id)from, (rcc_class_id)to, buf, size, NULL);
#else /* HAVE_LIBRCC */
    return NULL;
#endif /* HAVE_LIBRCC */
}

char *xmms_rcc_fs(xmms_rcc_class from, xmms_rcc_class to, const char *fspath, const char *path, const char *filename) {
#ifdef HAVE_LIBRCC
    return (char*)rccFS(ctx, (rcc_class_id)from, (rcc_class_id)to, fspath, path, filename);
#else /* HAVE_LIBRCC */
    return NULL;
#endif /* HAVE_LIBRCC */
}

const char *xmms_rcc_string(const char *buf) {
#ifdef HAVE_LIBRCC
    return rccGetString((const rcc_string)buf);
#else /* HAVE_LIBRCC */
    return buf;
#endif /* HAVE_LIBRCC */
}

const char *xmms_rcc_get_language() {
    const char *lang;
#ifdef HAVE_LIBRCC
    lang = rccGetCurrentLanguageName(ctx);
#else /* HAVE_LIBRCC */
    lang = NULL;
#endif /* HAVE_LIBRCC */
    return xmms_rcc_get_639_2_name(lang);
}

#define ID3_ENCODING_ISO_8859_1   0x00
#define ID3_ENCODING_UTF16        0x01
#define ID3_ENCODING_UTF16BE      0x02
#define ID3_ENCODING_UTF8	  0x03

int xmms_rcc_get_id3v2_encoding() {
#ifdef HAVE_LIBRCC
    const char *name;
        
    name = rccGetCurrentCharsetName(ctx, (rcc_class_id)XMMS_RCC_ID3V2);
    if (!name) return ID3_ENCODING_ISO_8859_1;
    
    if ((!strcasecmp(name,"UTF-8"))||(!strcasecmp(name,"UTF8"))) return ID3_ENCODING_UTF8;
    if ((!strcasecmp(name,"UTF-16"))||(!strcasecmp(name,"UTF16"))||(!strcasecmp(name,"UTF16LE"))||(!strcasecmp(name,"UTF-16LE"))) return ID3_ENCODING_UTF16;
    if ((!strcasecmp(name,"UTF-16BE"))||(!strcasecmp(name,"UTF16BE"))) return ID3_ENCODING_UTF16BE;
#endif /* HAVE_LIBRCC */
    
    return ID3_ENCODING_ISO_8859_1;
}
