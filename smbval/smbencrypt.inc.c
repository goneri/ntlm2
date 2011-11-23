/* mod_ntlm file: $Id: smbencrypt.inc.c,v 1.2 2003/02/21 01:55:14 casz Exp $ */

/* 
 * Unix SMB/Netbios implementation. Version 1.9. SMB parameters and
 * setup Copyright (C) Andrew Tridgell 1992-1997 Modified by Jeremy
 * Allison 1995.  This program is free software; you can redistribute
 * it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.  You should have received
 * a copy of the GNU General Public License along with this program;
 * if not, write to the Free Software Foundation, Inc., 675 Mass Ave,
 * Cambridge, MA 02139, USA. */

#include <string.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <string.h>
#include <sys/vfs.h>
#include <netinet/in.h>

#include "smblib-priv.h"
#define uchar unsigned char

#include "byteorder.h"

static char *StrnCpy(char *dest, char *src, int n);
static void strupper(char *s);

/* 
 * This implements the X/Open SMB password encryption It takes a password, 
 * a 8 byte "crypt key" and puts 24 bytes of  encrypted password into p24 */
static void 
SMBencrypt(uchar * passwd, uchar * c8, uchar * p24)
{
    uchar p14[15], p21[21];

    memset(p21, '\0', 21);
    memset(p14, '\0', 14);
    StrnCpy((char *) p14, (char *) passwd, 14);

    strupper((char *) p14);
    E_P16(p14, p21);
    E_P24(p21, c8, p24);
}

/****************************************************************************
line strncpy but always null terminates. Make sure there is room!
****************************************************************************/
static char *
StrnCpy(char *dest, char *src, int n)
{
    char *d = dest;
    if (!dest)
        return (NULL);
    if (!src) {
        *dest = 0;
        return (dest);
    }
    while (n-- && (*d++ = *src++)) ;
    *d = 0;
    return (dest);
}

static void 
strupper(char *s)
{
    while (*s) {
        if (islower((int) *s))
            *s = toupper(*s);
        s++;
    }
}
