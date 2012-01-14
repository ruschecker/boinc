/*
  Copyright (c) 1990-1999 Info-ZIP.  All rights reserved.

  See the accompanying file LICENSE, version 1999-Oct-05 or later
  (the contents of which are also included in zip.h) for terms of use.
  If, for some reason, both of these files are missing, the Info-ZIP license
  also may be found at:  ftp://ftp.cdrom.com/pub/infozip/license.html
*/
/*---------------------------------------------------------------------------

  ebcdic.h

  The CECP 1047 (Extended de-facto EBCDIC) <-> ISO 8859-1 conversion tables,
  from ftp://aix1.segi.ulg.ac.be/pub/docs/iso8859/iso8859.networking

  NOTES:
  <Paul_von_Behren@stortek.com> (OS/390 port 12/97)
   These table no longer represent the standard mappings (for example in the
   OS/390 iconv utility).  In order to follow current standards I remapped
     ebcdic x0a to ascii x15    and
     ebcdic x85 to ascii x25    (and vice-versa)
   Without these changes, newlines in auto-convert text files appeared
   as literal \045.
   I'm not sure what effect this remap would have on the MVS and CMS ports, so
   I ifdef'd these changes.  Hopefully these ifdef's can be removed when the
   MVS/CMS folks test the new mappings.

  Christian Spieler <spieler@ikp.tu-darmstadt.de>, 27-Apr-1998
   The problem mentioned by Paul von Behren was already observed previously
   on VM/CMS, during the preparation of the CMS&MVS port of UnZip 5.20 in
   1996. At that point, the ebcdic tables were not changed since they seemed
   to be an adopted standard (to my knowledge, these tables are still used
   as presented in mainfraime KERMIT). Instead, the "end-of-line" conversion
   feature of Zip's and UnZip's "text-translation" mode was used to force
   correct mappings between ASCII and EBCDIC newline markers.
   Before interchanging the ASCII mappings of the EBCDIC control characters
   "NL" 0x25 and "LF" 0x15 according to the OS/390 setting, we have to
   make sure that EBCDIC 0x15 is never used as line termination.

  ---------------------------------------------------------------------------*/

#ifndef __ebcdic_h      /* prevent multiple inclusions */
#define __ebcdic_h


#ifndef ZCONST
#  define ZCONST const
#endif

#ifdef EBCDIC
#ifndef MTS             /* MTS uses a slightly "special" EBCDIC code page */

ZCONST uch ebcdic[] = {
    0x00, 0x01, 0x02, 0x03, 0x37, 0x2D, 0x2E, 0x2F,  /* 00 - 07 */
#ifdef OS390
    0x16, 0x05, 0x15, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,  /* 08 - 0F */
#else
    0x16, 0x05, 0x25, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,  /* 08 - 0F */
#endif
    0x10, 0x11, 0x12, 0x13, 0x3C, 0x3D, 0x32, 0x26,  /* 10 - 17 */
    0x18, 0x19, 0x3F, 0x27, 0x1C, 0x1D, 0x1E, 0x1F,  /* 18 - 1F */
    0x40, 0x5A, 0x7F, 0x7B, 0x5B, 0x6C, 0x50, 0x7D,  /* 20 - 27 */
    0x4D, 0x5D, 0x5C, 0x4E, 0x6B, 0x60, 0x4B, 0x61,  /* 28 - 2F */
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,  /* 30 - 37 */
    0xF8, 0xF9, 0x7A, 0x5E, 0x4C, 0x7E, 0x6E, 0x6F,  /* 38 - 3F */
    0x7C, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,  /* 40 - 47 */
    0xC8, 0xC9, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,  /* 48 - 4F */
    0xD7, 0xD8, 0xD9, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,  /* 50 - 57 */
    0xE7, 0xE8, 0xE9, 0xAD, 0xE0, 0xBD, 0x5F, 0x6D,  /* 58 - 5F */
    0x79, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,  /* 60 - 67 */
    0x88, 0x89, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,  /* 68 - 6F */
    0x97, 0x98, 0x99, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6,  /* 70 - 77 */
    0xA7, 0xA8, 0xA9, 0xC0, 0x4F, 0xD0, 0xA1, 0x07,  /* 78 - 7F */
#ifdef OS390
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x06, 0x17,  /* 80 - 87 */
#else
    0x20, 0x21, 0x22, 0x23, 0x24, 0x15, 0x06, 0x17,  /* 80 - 87 */
#endif
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x09, 0x0A, 0x1B,  /* 88 - 8F */
    0x30, 0x31, 0x1A, 0x33, 0x34, 0x35, 0x36, 0x08,  /* 90 - 97 */
    0x38, 0x39, 0x3A, 0x3B, 0x04, 0x14, 0x3E, 0xFF,  /* 98 - 9F */
    0x41, 0xAA, 0x4A, 0xB1, 0x9F, 0xB2, 0x6A, 0xB5,  /* A0 - A7 */
    0xBB, 0xB4, 0x9A, 0x8A, 0xB0, 0xCA, 0xAF, 0xBC,  /* A8 - AF */
    0x90, 0x8F, 0xEA, 0xFA, 0xBE, 0xA0, 0xB6, 0xB3,  /* B0 - B7 */
    0x9D, 0xDA, 0x9B, 0x8B, 0xB7, 0xB8, 0xB9, 0xAB,  /* B8 - BF */
    0x64, 0x65, 0x62, 0x66, 0x63, 0x67, 0x9E, 0x68,  /* C0 - C7 */
    0x74, 0x71, 0x72, 0x73, 0x78, 0x75, 0x76, 0x77,  /* C8 - CF */
    0xAC, 0x69, 0xED, 0xEE, 0xEB, 0xEF, 0xEC, 0xBF,  /* D0 - D7 */
    0x80, 0xFD, 0xFE, 0xFB, 0xFC, 0xBA, 0xAE, 0x59,  /* D8 - DF */
    0x44, 0x45, 0x42, 0x46, 0x43, 0x47, 0x9C, 0x48,  /* E0 - E7 */
    0x54, 0x51, 0x52, 0x53, 0x58, 0x55, 0x56, 0x57,  /* E8 - EF */
    0x8C, 0x49, 0xCD, 0xCE, 0xCB, 0xCF, 0xCC, 0xE1,  /* F0 - F7 */
    0x70, 0xDD, 0xDE, 0xDB, 0xDC, 0x8D, 0x8E, 0xDF   /* F8 - FF */
};

#if (defined(ZIP) || CRYPT)
ZCONST uch ascii[] = {
    0x00, 0x01, 0x02, 0x03, 0x9C, 0x09, 0x86, 0x7F,  /* 00 - 07 */
    0x97, 0x8D, 0x8E, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,  /* 08 - 0F */
#ifdef OS390
    0x10, 0x11, 0x12, 0x13, 0x9D, 0x0A, 0x08, 0x87,  /* 10 - 17 */
#else
    0x10, 0x11, 0x12, 0x13, 0x9D, 0x85, 0x08, 0x87,  /* 10 - 17 */
#endif
    0x18, 0x19, 0x92, 0x8F, 0x1C, 0x1D, 0x1E, 0x1F,  /* 18 - 1F */
#ifdef OS390
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x17, 0x1B,  /* 20 - 27 */
#else
    0x80, 0x81, 0x82, 0x83, 0x84, 0x0A, 0x17, 0x1B,  /* 20 - 27 */
#endif
    0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x05, 0x06, 0x07,  /* 28 - 2F */
    0x90, 0x91, 0x16, 0x93, 0x94, 0x95, 0x96, 0x04,  /* 30 - 37 */
    0x98, 0x99, 0x9A, 0x9B, 0x14, 0x15, 0x9E, 0x1A,  /* 38 - 3F */
    0x20, 0xA0, 0xE2, 0xE4, 0xE0, 0xE1, 0xE3, 0xE5,  /* 40 - 47 */
    0xE7, 0xF1, 0xA2, 0x2E, 0x3C, 0x28, 0x2B, 0x7C,  /* 48 - 4F */
    0x26, 0xE9, 0xEA, 0xEB, 0xE8, 0xED, 0xEE, 0xEF,  /* 50 - 57 */
    0xEC, 0xDF, 0x21, 0x24, 0x2A, 0x29, 0x3B, 0x5E,  /* 58 - 5F */
    0x2D, 0x2F, 0xC2, 0xC4, 0xC0, 0xC1, 0xC3, 0xC5,  /* 60 - 67 */
    0xC7, 0xD1, 0xA6, 0x2C, 0x25, 0x5F, 0x3E, 0x3F,  /* 68 - 6F */
    0xF8, 0xC9, 0xCA, 0xCB, 0xC8, 0xCD, 0xCE, 0xCF,  /* 70 - 77 */
    0xCC, 0x60, 0x3A, 0x23, 0x40, 0x27, 0x3D, 0x22,  /* 78 - 7F */
    0xD8, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,  /* 80 - 87 */
    0x68, 0x69, 0xAB, 0xBB, 0xF0, 0xFD, 0xFE, 0xB1,  /* 88 - 8F */
    0xB0, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,  /* 90 - 97 */
    0x71, 0x72, 0xAA, 0xBA, 0xE6, 0xB8, 0xC6, 0xA4,  /* 98 - 9F */
    0xB5, 0x7E, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,  /* A0 - A7 */
    0x79, 0x7A, 0xA1, 0xBF, 0xD0, 0x5B, 0xDE, 0xAE,  /* A8 - AF */
    0xAC, 0xA3, 0xA5, 0xB7, 0xA9, 0xA7, 0xB6, 0xBC,  /* B0 - B7 */
    0xBD, 0xBE, 0xDD, 0xA8, 0xAF, 0x5D, 0xB4, 0xD7,  /* B8 - BF */
    0x7B, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,  /* C0 - C7 */
    0x48, 0x49, 0xAD, 0xF4, 0xF6, 0xF2, 0xF3, 0xF5,  /* C8 - CF */
    0x7D, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  /* D0 - D7 */
    0x51, 0x52, 0xB9, 0xFB, 0xFC, 0xF9, 0xFA, 0xFF,  /* D8 - DF */
    0x5C, 0xF7, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  /* E0 - E7 */
    0x59, 0x5A, 0xB2, 0xD4, 0xD6, 0xD2, 0xD3, 0xD5,  /* E8 - EF */
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,  /* F0 - F7 */
    0x38, 0x39, 0xB3, 0xDB, 0xDC, 0xD9, 0xDA, 0x9F   /* F8 - FF */
};
#endif /* ZIP || CRYPT */

#else /* MTS */

/*
 * This is the MTS ASCII->EBCDIC translation table. It provides a 1-1
 * translation from ISO 8859/1 8-bit ASCII to IBM Code Page 37 EBCDIC.
 */

ZCONST uch ebcdic[] = {
    0x00, 0x01, 0x02, 0x03, 0x37, 0x2D, 0x2E, 0x2F,  /* 00 - 07 */
    0x16, 0x05, 0x25, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,  /* 08 - 0F */
    0x10, 0x11, 0x12, 0x13, 0x3C, 0x3D, 0x32, 0x26,  /* 10 - 17 */
    0x18, 0x19, 0x3F, 0x27, 0x1C, 0x1D, 0x1E, 0x1F,  /* 18 - 1F */
    0x40, 0x5A, 0x7F, 0x7B, 0x5B, 0x6C, 0x50, 0x7D,  /* 20 - 27 */
    0x4D, 0x5D, 0x5C, 0x4E, 0x6B, 0x60, 0x4B, 0x61,  /* 28 - 2F */
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,  /* 30 - 37 */
    0xF8, 0xF9, 0x7A, 0x5E, 0x4C, 0x7E, 0x6E, 0x6F,  /* 38 - 3F */
    0x7C, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,  /* 40 - 47 */
    0xC8, 0xC9, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,  /* 48 - 4F */
    0xD7, 0xD8, 0xD9, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,  /* 50 - 57 */
    0xE7, 0xE8, 0xE9, 0xBA, 0xE0, 0xBB, 0xB0, 0x6D,  /* 58 - 5F */
    0x79, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,  /* 60 - 67 */
    0x88, 0x89, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,  /* 68 - 6F */
    0x97, 0x98, 0x99, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6,  /* 70 - 77 */
    0xA7, 0xA8, 0xA9, 0xC0, 0x4F, 0xD0, 0xA1, 0x07,  /* 78 - 7F */
    0x20, 0x21, 0x22, 0x23, 0x24, 0x15, 0x06, 0x17,  /* 80 - 87 */
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x09, 0x0A, 0x1B,  /* 88 - 8F */
    0x30, 0x31, 0x1A, 0x33, 0x34, 0x35, 0x36, 0x08,  /* 90 - 97 */
    0x38, 0x39, 0x3A, 0x3B, 0x04, 0x14, 0x3E, 0xFF,  /* 98 - 9F */
    0x41, 0xAA, 0x4A, 0xB1, 0x9F, 0xB2, 0x6A, 0xB5,  /* A0 - A7 */
    0xBD, 0xB4, 0x9A, 0x8A, 0x5F, 0xCA, 0xAF, 0xBC,  /* A8 - AF */
    0x90, 0x8F, 0xEA, 0xFA, 0xBE, 0xA0, 0xB6, 0xB3,  /* B0 - B7 */
    0x9D, 0xDA, 0x9B, 0x8B, 0xB7, 0xB8, 0xB9, 0xAB,  /* B8 - BF */
    0x64, 0x65, 0x62, 0x66, 0x63, 0x67, 0x9E, 0x68,  /* C0 - C7 */
    0x74, 0x71, 0x72, 0x73, 0x78, 0x75, 0x76, 0x77,  /* C8 - CF */
    0xAC, 0x69, 0xED, 0xEE, 0xEB, 0xEF, 0xEC, 0xBF,  /* D0 - D7 */
    0x80, 0xFD, 0xFE, 0xFB, 0xFC, 0xAD, 0xAE, 0x59,  /* D8 - DF */
    0x44, 0x45, 0x42, 0x46, 0x43, 0x47, 0x9C, 0x48,  /* E0 - E7 */
    0x54, 0x51, 0x52, 0x53, 0x58, 0x55, 0x56, 0x57,  /* E8 - EF */
    0x8C, 0x49, 0xCD, 0xCE, 0xCB, 0xCF, 0xCC, 0xE1,  /* F0 - F7 */
    0x70, 0xDD, 0xDE, 0xDB, 0xDC, 0x8D, 0x8E, 0xDF   /* F8 - FF */
};

#if (defined(ZIP) || CRYPT)
ZCONST uch ascii[] = {
    0x00, 0x01, 0x02, 0x03, 0x9C, 0x09, 0x86, 0x7F,  /* 00 - 07 */
    0x97, 0x8D, 0x8E, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,  /* 08 - 0F */
    0x10, 0x11, 0x12, 0x13, 0x9D, 0x85, 0x08, 0x87,  /* 10 - 17 */
    0x18, 0x19, 0x92, 0x8F, 0x1C, 0x1D, 0x1E, 0x1F,  /* 18 - 1F */
    0x80, 0x81, 0x82, 0x83, 0x84, 0x0A, 0x17, 0x1B,  /* 20 - 27 */
    0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x05, 0x06, 0x07,  /* 28 - 2F */
    0x90, 0x91, 0x16, 0x93, 0x94, 0x95, 0x96, 0x04,  /* 30 - 37 */
    0x98, 0x99, 0x9A, 0x9B, 0x14, 0x15, 0x9E, 0x1A,  /* 38 - 3F */
    0x20, 0xA0, 0xE2, 0xE4, 0xE0, 0xE1, 0xE3, 0xE5,  /* 40 - 47 */
    0xE7, 0xF1, 0xA2, 0x2E, 0x3C, 0x28, 0x2B, 0x7C,  /* 48 - 4F */
    0x26, 0xE9, 0xEA, 0xEB, 0xE8, 0xED, 0xEE, 0xEF,  /* 50 - 57 */
    0xEC, 0xDF, 0x21, 0x24, 0x2A, 0x29, 0x3B, 0xAC,  /* 58 - 5F */
    0x2D, 0x2F, 0xC2, 0xC4, 0xC0, 0xC1, 0xC3, 0xC5,  /* 60 - 67 */
    0xC7, 0xD1, 0xA6, 0x2C, 0x25, 0x5F, 0x3E, 0x3F,  /* 68 - 6F */
    0xF8, 0xC9, 0xCA, 0xCB, 0xC8, 0xCD, 0xCE, 0xCF,  /* 70 - 77 */
    0xCC, 0x60, 0x3A, 0x23, 0x40, 0x27, 0x3D, 0x22,  /* 78 - 7F */
    0xD8, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,  /* 80 - 87 */
    0x68, 0x69, 0xAB, 0xBB, 0xF0, 0xFD, 0xFE, 0xB1,  /* 88 - 8F */
    0xB0, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,  /* 90 - 97 */
    0x71, 0x72, 0xAA, 0xBA, 0xE6, 0xB8, 0xC6, 0xA4,  /* 98 - 9F */
    0xB5, 0x7E, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,  /* A0 - A7 */
    0x79, 0x7A, 0xA1, 0xBF, 0xD0, 0xDD, 0xDE, 0xAE,  /* A8 - AF */
    0x5E, 0xA3, 0xA5, 0xB7, 0xA9, 0xA7, 0xB6, 0xBC,  /* B0 - B7 */
    0xBD, 0xBE, 0x5B, 0x5D, 0xAF, 0xA8, 0xB4, 0xD7,  /* B8 - BF */
    0x7B, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,  /* C0 - C7 */
    0x48, 0x49, 0xAD, 0xF4, 0xF6, 0xF2, 0xF3, 0xF5,  /* C8 - CF */
    0x7D, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,  /* D0 - D7 */
    0x51, 0x52, 0xB9, 0xFB, 0xFC, 0xF9, 0xFA, 0xFF,  /* D8 - DF */
    0x5C, 0xF7, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,  /* E0 - E7 */
    0x59, 0x5A, 0xB2, 0xD4, 0xD6, 0xD2, 0xD3, 0xD5,  /* E8 - EF */
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,  /* F0 - F7 */
    0x38, 0x39, 0xB3, 0xDB, 0xDC, 0xD9, 0xDA, 0x9F   /* F8 - FF */
};
#endif /* ZIP || CRYPT */

#endif /* ?MTS */
#endif /* EBCDIC */

/*---------------------------------------------------------------------------

  The following conversion tables translate between IBM PC CP 850
  (OEM codepage) and the "Western Europe & America" Windows codepage 1252.
  The Windows codepage 1252 contains the ISO 8859-1 "Latin 1" codepage,
  with some additional printable characters in the range (0x80 - 0x9F),
  that is reserved to control codes in the ISO 8859-1 character table.

  The ISO <--> OEM conversion tables were constructed with the help
  of the WIN32 (Win16?) API's OemToAnsi() and AnsiToOem() conversion
  functions and have been checked against the CP850 and LATIN1 tables
  provided in the MS-Kermit 3.14 distribution.

  ---------------------------------------------------------------------------*/

#ifdef IZ_ISO2OEM_ARRAY
ZCONST uch Far iso2oem[] = {
    0x3F, 0x3F, 0x27, 0x9F, 0x22, 0x2E, 0xC5, 0xCE,  /* 80 - 87 */
    0x5E, 0x25, 0x53, 0x3C, 0x4F, 0x3F, 0x3F, 0x3F,  /* 88 - 8F */
    0x3F, 0x27, 0x27, 0x22, 0x22, 0x07, 0x2D, 0x2D,  /* 90 - 97 */
    0x7E, 0x54, 0x73, 0x3E, 0x6F, 0x3F, 0x3F, 0x59,  /* 98 - 9F */
    0xFF, 0xAD, 0xBD, 0x9C, 0xCF, 0xBE, 0xDD, 0xF5,  /* A0 - A7 */
    0xF9, 0xB8, 0xA6, 0xAE, 0xAA, 0xF0, 0xA9, 0xEE,  /* A8 - AF */
    0xF8, 0xF1, 0xFD, 0xFC, 0xEF, 0xE6, 0xF4, 0xFA,  /* B0 - B7 */
    0xF7, 0xFB, 0xA7, 0xAF, 0xAC, 0xAB, 0xF3, 0xA8,  /* B8 - BF */
    0xB7, 0xB5, 0xB6, 0xC7, 0x8E, 0x8F, 0x92, 0x80,  /* C0 - C7 */
    0xD4, 0x90, 0xD2, 0xD3, 0xDE, 0xD6, 0xD7, 0xD8,  /* C8 - CF */
    0xD1, 0xA5, 0xE3, 0xE0, 0xE2, 0xE5, 0x99, 0x9E,  /* D0 - D7 */
    0x9D, 0xEB, 0xE9, 0xEA, 0x9A, 0xED, 0xE8, 0xE1,  /* D8 - DF */
    0x85, 0xA0, 0x83, 0xC6, 0x84, 0x86, 0x91, 0x87,  /* E0 - E7 */
    0x8A, 0x82, 0x88, 0x89, 0x8D, 0xA1, 0x8C, 0x8B,  /* E8 - EF */
    0xD0, 0xA4, 0x95, 0xA2, 0x93, 0xE4, 0x94, 0xF6,  /* F0 - F7 */
    0x9B, 0x97, 0xA3, 0x96, 0x81, 0xEC, 0xE7, 0x98   /* F8 - FF */
};
#endif /* IZ_ISO2OEM_ARRAY */

#ifdef IZ_OEM2ISO_ARRAY
ZCONST uch Far oem2iso[] = {
    0xC7, 0xFC, 0xE9, 0xE2, 0xE4, 0xE0, 0xE5, 0xE7,  /* 80 - 87 */
    0xEA, 0xEB, 0xE8, 0xEF, 0xEE, 0xEC, 0xC4, 0xC5,  /* 88 - 8F */
    0xC9, 0xE6, 0xC6, 0xF4, 0xF6, 0xF2, 0xFB, 0xF9,  /* 90 - 97 */
    0xFF, 0xD6, 0xDC, 0xF8, 0xA3, 0xD8, 0xD7, 0x83,  /* 98 - 9F */
    0xE1, 0xED, 0xF3, 0xFA, 0xF1, 0xD1, 0xAA, 0xBA,  /* A0 - A7 */
    0xBF, 0xAE, 0xAC, 0xBD, 0xBC, 0xA1, 0xAB, 0xBB,  /* A8 - AF */
    0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xC1, 0xC2, 0xC0,  /* B0 - B7 */
    0xA9, 0xA6, 0xA6, 0x2B, 0x2B, 0xA2, 0xA5, 0x2B,  /* B8 - BF */
    0x2B, 0x2D, 0x2D, 0x2B, 0x2D, 0x2B, 0xE3, 0xC3,  /* C0 - C7 */
    0x2B, 0x2B, 0x2D, 0x2D, 0xA6, 0x2D, 0x2B, 0xA4,  /* C8 - CF */
    0xF0, 0xD0, 0xCA, 0xCB, 0xC8, 0x69, 0xCD, 0xCE,  /* D0 - D7 */
    0xCF, 0x2B, 0x2B, 0xA6, 0x5F, 0xA6, 0xCC, 0xAF,  /* D8 - DF */
    0xD3, 0xDF, 0xD4, 0xD2, 0xF5, 0xD5, 0xB5, 0xFE,  /* E0 - E7 */
    0xDE, 0xDA, 0xDB, 0xD9, 0xFD, 0xDD, 0xAF, 0xB4,  /* E8 - EF */
    0xAD, 0xB1, 0x3D, 0xBE, 0xB6, 0xA7, 0xF7, 0xB8,  /* F0 - F7 */
    0xB0, 0xA8, 0xB7, 0xB9, 0xB3, 0xB2, 0xA6, 0xA0   /* F8 - FF */
};
#endif /* IZ_OEM2ISO_ARRAY */

#if defined(THEOS) || defined(THEOS_SUPPORT)
#  include "theos/charconv.h"
#endif

#endif /* __ebcdic_h  */
