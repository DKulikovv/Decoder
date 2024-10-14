/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Universal charset detector code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2001
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *          BYVoid <byvoid.kcp@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "../uchardet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef VERSION
#define VERSION "Unknown"
#endif
#define BUFFER_SIZE 65536

static char buffer[BUFFER_SIZE];

static void detect(uchardet_t  handle,
                   FILE       *fp,
                   bool        show_lang,
                   bool        verbose)
{
    while (1)
    {
        size_t len = fread(buffer, 1, BUFFER_SIZE, fp);
        if (len == 0)
            break;
        int retval = uchardet_handle_data(handle, buffer, len);
        if (retval != 0)
        {
            fprintf(stderr, "Handle data error.\n");
            exit(1);
        }
    }
    uchardet_data_end(handle);

    if (verbose)
    {
        size_t candidates = uchardet_get_n_candidates(handle);
        size_t i;

        printf("\n");
        for (i = 0; i < candidates; i++)
        {
            if (uchardet_get_language(handle, i))
                printf("\t%s / %s (%f)\n",
                        uchardet_get_encoding(handle, i),
                        uchardet_get_language(handle, i),
                        uchardet_get_confidence(handle, i));
            else
                printf("\t%s (%f)\n",
                        uchardet_get_encoding(handle, i),
                        uchardet_get_confidence(handle, i));
        }
    }
    else if (show_lang)
    {
        const char *lang = uchardet_get_language(handle, 0);
        if (lang && *lang)
            printf("%s\n", lang);
        else
            printf("unknown\n");
    }
    else
    {
        const char *charset = uchardet_get_encoding(handle, 0);
        if (*charset)
            printf("%s\n", charset);
        else
            printf("unknown\n");
    }

    uchardet_reset(handle);
}

static void show_version()
{
    printf("\n");
    printf("uchardet Command Line Tool\n");
    printf("Version %s\n", VERSION);
    printf("\n");
    printf("Authors: %s\n", "BYVoid, Jehan");
    printf("Bug Report: %s\n", "https://gitlab.freedesktop.org/uchardet/uchardet/-/issues");
    printf("\n");
}

static void show_usage()
{
    show_version();
    printf("Usage:\n");
    printf(" uchardet [Options] [File]...\n");
    printf("\n");
    printf("Options:\n");
    printf(" -v, --version         Print version and build information.\n");
    printf(" -h, --help            Print this help.\n");
    printf(" -l, --language        Print the detected language (as ISO 639-1 code) rather than encoding.\n");
    printf(" -V, --verbose         Show all candidates and their confidence value.\n");
    printf(" -w, --weight          Tweak language weights.\n");
    printf("\n");
}

int main(int argc, char ** argv)
{
    return 0;
}
