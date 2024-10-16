/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *                 Jehan <jehan@girinstud.io>
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

#include "src/nsSBCharSetProber.h"

/********* Language model for: Danish *********/

/**
 * Generated by BuildLangModel.py
 * On: 2016-05-04 10:31:41.266956
 **/

/* Character Mapping Table:
 * ILL: illegal character.
 * CTR: control character specific to the charset.
 * RET: carriage/return.
 * SYM: symbol (punctuation) that does not belong to word.
 * NUM: 0 - 9.
 *
 * Other characters are ordered by probabilities
 * (0 is the most common character in the language).
 *
 * Orders are generic to a language. So the codepoint with order X in
 * CHARSET1 maps to the same character as the codepoint with the same
 * order X in CHARSET2 for the same language.
 * As such, it is possible to get missing order. For instance the
 * ligature of 'o' and 'e' exists in ISO-8859-15 but not in ISO-8859-1
 * even though they are both used for French. Same for the euro sign.
 */
static unsigned char Latin15CharToOrderMap[] =
{
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,RET,CTR,CTR,RET,CTR,CTR, /* 0X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 1X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* 2X */
  NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,SYM,SYM,SYM,SYM,SYM,SYM, /* 3X */
  SYM,  4, 15, 23,  7,  0, 13, 10, 18,  6, 24, 11,  8, 12,  2,  9, /* 4X */
   17, 30,  1,  5,  3, 16, 14, 25, 27, 19, 26,SYM,SYM,SYM,SYM,SYM, /* 5X */
  SYM,  4, 15, 23,  7,  0, 13, 10, 18,  6, 24, 11,  8, 12,  2,  9, /* 6X */
   17, 30,  1,  5,  3, 16, 14, 25, 27, 19, 26,SYM,SYM,SYM,SYM,CTR, /* 7X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 8X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 9X */
  SYM,SYM,SYM,SYM,SYM,SYM, 42,SYM, 42,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* AX */
  SYM,SYM,SYM,SYM, 53, 54,SYM,SYM, 55,SYM,SYM,SYM, 46, 46, 56,SYM, /* BX */
   47, 31, 43, 48, 36, 21, 22, 37, 39, 28, 49, 50, 57, 33, 58, 59, /* CX */
   29, 45, 51, 34, 40, 60, 35,SYM, 20, 61, 38, 52, 32, 41, 62, 44, /* DX */
   47, 31, 43, 48, 36, 21, 22, 37, 39, 28, 49, 50, 63, 33, 64, 65, /* EX */
   29, 45, 51, 34, 40, 66, 35,SYM, 20, 67, 38, 52, 32, 41, 68, 69, /* FX */
};
/*X0  X1  X2  X3  X4  X5  X6  X7  X8  X9  XA  XB  XC  XD  XE  XF */

static unsigned char Latin1CharToOrderMap[] =
{
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,RET,CTR,CTR,RET,CTR,CTR, /* 0X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 1X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* 2X */
  NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,SYM,SYM,SYM,SYM,SYM,SYM, /* 3X */
  SYM,  4, 15, 23,  7,  0, 13, 10, 18,  6, 24, 11,  8, 12,  2,  9, /* 4X */
   17, 30,  1,  5,  3, 16, 14, 25, 27, 19, 26,SYM,SYM,SYM,SYM,SYM, /* 5X */
  SYM,  4, 15, 23,  7,  0, 13, 10, 18,  6, 24, 11,  8, 12,  2,  9, /* 6X */
   17, 30,  1,  5,  3, 16, 14, 25, 27, 19, 26,SYM,SYM,SYM,SYM,CTR, /* 7X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 8X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 9X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* AX */
  SYM,SYM,SYM,SYM,SYM, 70,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* BX */
   47, 31, 43, 48, 36, 21, 22, 37, 39, 28, 49, 50, 71, 33, 72, 73, /* CX */
   29, 45, 51, 34, 40, 74, 35,SYM, 20, 75, 38, 52, 32, 41, 76, 44, /* DX */
   47, 31, 43, 48, 36, 21, 22, 37, 39, 28, 49, 50, 77, 33, 78, 79, /* EX */
   29, 45, 51, 34, 40, 80, 35,SYM, 20, 81, 38, 52, 32, 41, 82, 83, /* FX */
};
/*X0  X1  X2  X3  X4  X5  X6  X7  X8  X9  XA  XB  XC  XD  XE  XF */

static unsigned char Windows1252CharToOrderMap[] =
{
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,RET,CTR,CTR,RET,CTR,CTR, /* 0X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 1X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* 2X */
  NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,SYM,SYM,SYM,SYM,SYM,SYM, /* 3X */
  SYM,  4, 15, 23,  7,  0, 13, 10, 18,  6, 24, 11,  8, 12,  2,  9, /* 4X */
   17, 30,  1,  5,  3, 16, 14, 25, 27, 19, 26,SYM,SYM,SYM,SYM,SYM, /* 5X */
  SYM,  4, 15, 23,  7,  0, 13, 10, 18,  6, 24, 11,  8, 12,  2,  9, /* 6X */
   17, 30,  1,  5,  3, 16, 14, 25, 27, 19, 26,SYM,SYM,SYM,SYM,CTR, /* 7X */
  SYM,ILL,SYM, 84,SYM,SYM,SYM,SYM,SYM,SYM, 42,SYM, 46,ILL, 85,ILL, /* 8X */
  ILL,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, 42,SYM, 46,ILL, 86, 87, /* 9X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* AX */
  SYM,SYM,SYM,SYM,SYM, 88,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* BX */
   47, 31, 43, 48, 36, 21, 22, 37, 39, 28, 49, 50, 89, 33, 90, 91, /* CX */
   29, 45, 51, 34, 40, 92, 35,SYM, 20, 93, 38, 52, 32, 41, 94, 44, /* DX */
   47, 31, 43, 48, 36, 21, 22, 37, 39, 28, 49, 50, 95, 33, 96, 97, /* EX */
   29, 45, 51, 34, 40, 98, 35,SYM, 20, 99, 38, 52, 32, 41,100,101, /* FX */
};
/*X0  X1  X2  X3  X4  X5  X6  X7  X8  X9  XA  XB  XC  XD  XE  XF */


/* Model Table:
 * Total sequences: 983
 * First 512 sequences: 0.9959064368974055
 * Next 512 sequences (512-1024): 0.004093563102594482
 * Rest: -2.688821387764051e-17
 * Negative sequences: TODO
 */
static char DanishLangModel[] =
{
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,3,3,3,2,3,0,0,2,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,2,3,2,2,0,2,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,0,0,
  3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,3,3,2,2,2,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,0,2,0,2,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,0,2,3,2,2,3,2,2,2,2,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,2,2,0,2,0,0,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,2,2,0,2,0,2,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,0,3,3,3,2,2,2,2,2,
  3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,2,3,3,3,3,3,2,3,2,0,0,2,0,2,
  3,3,3,3,3,3,3,2,3,3,2,3,3,3,3,2,3,2,3,3,3,3,3,2,3,2,2,0,0,0,2,
  3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,3,0,2,
  3,3,3,3,3,3,3,3,3,3,3,2,2,3,3,2,3,2,3,3,3,3,3,2,3,0,2,3,2,0,0,
  3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,2,2,3,3,3,3,2,3,2,0,0,2,0,0,
  3,3,3,3,3,3,3,2,3,3,2,2,2,2,2,3,3,2,2,3,3,3,3,2,3,2,0,0,2,0,0,
  3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,2,3,3,2,2,0,2,3,2,2,2,3,0,3,2,
  3,3,3,3,3,3,3,3,3,3,3,2,2,3,3,3,3,3,3,2,3,3,3,2,2,0,2,0,2,0,0,
  3,3,3,3,3,3,3,2,3,3,2,2,3,2,3,2,3,2,2,3,3,3,3,2,3,3,2,2,2,0,0,
  3,3,3,3,3,3,2,3,3,3,3,3,3,2,3,3,2,3,3,0,2,0,0,2,0,2,2,0,0,0,0,
  3,3,3,3,2,3,2,3,3,2,3,3,3,2,3,3,2,2,2,2,0,0,0,0,3,0,2,0,0,0,0,
  3,3,3,3,0,3,0,3,3,2,3,3,2,2,3,3,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,
  2,3,3,3,2,3,3,3,3,2,3,3,3,3,3,3,2,2,2,0,0,0,0,2,0,0,0,2,0,0,0,
  3,3,2,3,3,2,3,2,3,3,2,3,2,2,2,2,3,2,3,3,0,0,2,3,0,2,2,0,2,0,2,
  3,3,3,3,3,3,2,3,3,3,2,2,2,2,2,2,3,2,2,2,3,2,3,0,2,0,0,0,2,0,0,
  3,2,2,2,3,2,3,2,2,3,0,2,0,0,0,2,2,2,2,2,0,0,0,2,0,2,2,0,0,0,0,
  3,0,2,2,3,2,3,2,2,3,0,2,2,0,0,2,2,2,2,2,0,0,0,0,0,2,2,0,0,0,0,
  3,2,0,2,2,2,3,0,2,2,0,2,2,2,2,2,0,2,2,2,2,0,0,2,0,2,0,2,0,0,0,
  2,3,3,2,0,2,0,2,2,0,2,2,2,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,
  0,2,2,0,2,2,2,0,0,2,0,0,0,0,0,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,2,0,0,0,2,2,0,0,0,0,0,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
};


SequenceModel Latin15_DanishModel =
{
  Latin15CharToOrderMap,
  DanishLangModel,
  31,
  (float)0.9959064368974055,
  PR_TRUE,
  "ISO-8859-15"
};

SequenceModel Latin1_DanishModel =
{
  Latin1CharToOrderMap,
  DanishLangModel,
  31,
  (float)0.9959064368974055,
  PR_TRUE,
  "ISO-8859-1"
};

SequenceModel Windows1252_DanishModel =
{
  Windows1252CharToOrderMap,
  DanishLangModel,
  31,
  (float)0.9959064368974055,
  PR_TRUE,
  "windows-1252"
};
