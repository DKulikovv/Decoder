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

/********* Language model for: Spanish *********/

/**
 * Generated by BuildLangModel.py
 * On: 2016-05-04 10:38:58.026209
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
static unsigned char Windows1252CharToOrderMap[] =
{
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,RET,CTR,CTR,RET,CTR,CTR, /* 0X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 1X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* 2X */
  NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,SYM,SYM,SYM,SYM,SYM,SYM, /* 3X */
  SYM,  1, 15, 10,  8,  0, 16, 14, 19,  5, 25, 28,  7, 12,  4,  2, /* 4X */
   13, 22,  6,  3,  9, 11, 18, 30, 27, 17, 24,SYM,SYM,SYM,SYM,SYM, /* 5X */
  SYM,  1, 15, 10,  8,  0, 16, 14, 19,  5, 25, 28,  7, 12,  4,  2, /* 6X */
   13, 22,  6,  3,  9, 11, 18, 30, 27, 17, 24,SYM,SYM,SYM,SYM,CTR, /* 7X */
  SYM,ILL,SYM, 52,SYM,SYM,SYM,SYM,SYM,SYM, 50,SYM, 53,ILL, 45,ILL, /* 8X */
  ILL,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, 50,SYM, 54,ILL, 45, 51, /* 9X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* AX */
  SYM,SYM,SYM,SYM,SYM, 40,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* BX */
   42, 23, 41, 43, 37, 48, 49, 36, 32, 26, 38, 34, 44, 21, 39, 55, /* CX */
   56, 29, 47, 20, 57, 58, 35,SYM, 59, 60, 31, 61, 33, 46, 62, 63, /* DX */
   42, 23, 41, 43, 37, 48, 49, 36, 32, 26, 38, 34, 44, 21, 39, 64, /* EX */
   65, 29, 47, 20, 66, 67, 35,SYM, 68, 69, 31, 70, 33, 46, 71, 51, /* FX */
};
/*X0  X1  X2  X3  X4  X5  X6  X7  X8  X9  XA  XB  XC  XD  XE  XF */

static unsigned char Latin1CharToOrderMap[] =
{
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,RET,CTR,CTR,RET,CTR,CTR, /* 0X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 1X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* 2X */
  NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,SYM,SYM,SYM,SYM,SYM,SYM, /* 3X */
  SYM,  1, 15, 10,  8,  0, 16, 14, 19,  5, 25, 28,  7, 12,  4,  2, /* 4X */
   13, 22,  6,  3,  9, 11, 18, 30, 27, 17, 24,SYM,SYM,SYM,SYM,SYM, /* 5X */
  SYM,  1, 15, 10,  8,  0, 16, 14, 19,  5, 25, 28,  7, 12,  4,  2, /* 6X */
   13, 22,  6,  3,  9, 11, 18, 30, 27, 17, 24,SYM,SYM,SYM,SYM,CTR, /* 7X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 8X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 9X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* AX */
  SYM,SYM,SYM,SYM,SYM, 40,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* BX */
   42, 23, 41, 43, 37, 48, 49, 36, 32, 26, 38, 34, 44, 21, 39, 72, /* CX */
   73, 29, 47, 20, 74, 75, 35,SYM, 76, 77, 31, 78, 33, 46, 79, 80, /* DX */
   42, 23, 41, 43, 37, 48, 49, 36, 32, 26, 38, 34, 44, 21, 39, 81, /* EX */
   82, 29, 47, 20, 83, 84, 35,SYM, 85, 86, 31, 87, 33, 46, 88, 51, /* FX */
};
/*X0  X1  X2  X3  X4  X5  X6  X7  X8  X9  XA  XB  XC  XD  XE  XF */

static unsigned char Latin15CharToOrderMap[] =
{
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,RET,CTR,CTR,RET,CTR,CTR, /* 0X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 1X */
  SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* 2X */
  NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,NUM,SYM,SYM,SYM,SYM,SYM,SYM, /* 3X */
  SYM,  1, 15, 10,  8,  0, 16, 14, 19,  5, 25, 28,  7, 12,  4,  2, /* 4X */
   13, 22,  6,  3,  9, 11, 18, 30, 27, 17, 24,SYM,SYM,SYM,SYM,SYM, /* 5X */
  SYM,  1, 15, 10,  8,  0, 16, 14, 19,  5, 25, 28,  7, 12,  4,  2, /* 6X */
   13, 22,  6,  3,  9, 11, 18, 30, 27, 17, 24,SYM,SYM,SYM,SYM,CTR, /* 7X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 8X */
  CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR,CTR, /* 9X */
  SYM,SYM,SYM,SYM,SYM,SYM, 50,SYM, 50,SYM,SYM,SYM,SYM,SYM,SYM,SYM, /* AX */
  SYM,SYM,SYM,SYM, 45, 40,SYM,SYM, 45,SYM,SYM,SYM, 89, 90, 51,SYM, /* BX */
   42, 23, 41, 43, 37, 48, 49, 36, 32, 26, 38, 34, 44, 21, 39, 91, /* CX */
   92, 29, 47, 20, 93, 94, 35,SYM, 95, 96, 31, 97, 33, 46, 98, 99, /* DX */
   42, 23, 41, 43, 37, 48, 49, 36, 32, 26, 38, 34, 44, 21, 39,100, /* EX */
  101, 29, 47, 20,102,103, 35,SYM,104,105, 31,106, 33, 46,107, 51, /* FX */
};
/*X0  X1  X2  X3  X4  X5  X6  X7  X8  X9  XA  XB  XC  XD  XE  XF */


/* Model Table:
 * Total sequences: 879
 * First 512 sequences: 0.9966324196921269
 * Next 512 sequences (512-1024): 0.003367580307873074
 * Rest: 2.2985086056692694e-17
 * Negative sequences: TODO
 */
static char SpanishLangModel[] =
{
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,0,3,3,3,3,2,0,0,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,0,3,3,3,2,3,3,3,3,0,0,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,2,3,2,3,3,2,3,3,2,3,0,0,0,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,3,0,3,0,3,2,0,0,
  3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,2,3,3,3,3,3,3,3,3,3,3,3,2,3,0,2,3,0,0,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,2,3,2,3,3,3,3,3,3,3,3,2,0,2,0,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,2,3,0,2,2,2,2,
  3,3,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,2,2,3,2,3,0,2,2,2,0,
  3,3,3,3,2,3,3,3,3,2,2,3,3,2,3,2,2,3,3,2,3,3,3,3,0,2,3,0,2,0,3,2,0,2,
  3,3,3,3,3,3,3,3,2,3,3,3,3,2,3,3,2,3,2,3,3,3,0,3,3,0,3,2,2,0,2,3,0,2,
  3,3,3,2,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,3,2,3,2,2,3,2,3,0,2,2,0,0,
  3,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,3,2,2,3,2,2,3,3,3,3,2,2,2,0,0,0,
  3,3,3,3,3,3,2,2,2,2,3,3,3,3,2,3,2,3,2,2,3,3,0,3,2,0,3,2,2,0,0,3,0,2,
  3,3,3,3,2,3,3,3,2,3,3,3,2,3,2,2,2,2,0,3,3,3,0,3,2,2,3,0,2,0,0,3,2,0,
  3,3,3,3,3,3,3,3,2,3,2,3,3,2,3,3,2,2,2,3,3,3,0,3,2,0,3,2,2,0,2,3,0,2,
  3,3,3,3,3,3,3,3,3,3,2,3,2,0,2,2,0,3,2,2,3,3,0,3,2,3,3,0,0,0,0,2,0,2,
  3,3,3,2,2,3,3,3,0,3,2,3,2,0,3,2,3,2,2,2,3,3,0,3,2,0,2,0,2,0,2,3,2,2,
  3,3,3,3,3,2,2,3,3,3,2,3,2,2,0,2,2,0,2,0,2,0,0,2,2,0,2,0,2,0,2,2,2,0,
  3,3,3,2,2,3,2,2,2,2,2,3,0,0,0,0,2,2,0,0,3,3,0,2,0,0,3,0,0,0,0,0,0,0,
  3,3,3,2,3,3,3,3,2,3,2,3,3,2,2,2,2,3,2,2,2,3,0,2,0,0,3,0,2,0,2,2,2,2,
  0,0,0,3,3,2,3,3,3,3,2,0,3,3,3,2,3,0,3,0,0,0,0,0,2,0,0,3,2,2,0,0,0,0,
  2,3,3,3,3,0,3,2,3,3,3,0,3,3,3,2,3,0,2,0,0,0,3,0,2,0,0,0,0,0,0,0,0,0,
  0,2,2,2,0,0,2,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  2,0,0,3,3,2,3,3,2,3,3,2,3,3,3,3,3,2,2,2,0,0,2,0,2,2,0,3,2,0,0,0,0,0,
  3,3,3,0,2,3,2,2,2,2,3,3,2,0,3,2,0,2,0,2,3,0,2,2,3,0,2,0,2,0,0,2,0,0,
  3,3,3,2,2,3,2,0,0,0,0,3,2,2,0,0,2,0,0,0,3,2,0,2,0,0,3,0,0,0,0,2,0,0,
  2,3,2,3,3,2,3,3,3,3,3,2,2,3,3,2,2,0,2,0,0,0,2,0,2,2,0,3,2,0,0,0,0,0,
  2,3,3,0,0,3,0,2,2,3,3,2,0,3,0,0,2,2,3,2,2,3,2,2,0,0,0,3,0,0,0,0,0,0,
  3,3,3,3,2,3,2,3,2,2,2,3,3,2,2,2,2,2,2,2,0,2,0,2,0,2,0,0,2,0,2,0,0,0,
  2,3,3,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,2,0,2,0,0,2,0,0,0,0,0,0,0,
  3,3,3,3,3,3,2,2,2,2,2,0,2,2,2,2,0,2,0,3,0,0,0,2,2,0,0,0,2,0,2,0,0,0,
  0,3,2,3,3,0,2,3,2,3,2,0,3,2,2,3,2,2,0,2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,
  0,0,0,2,2,0,2,0,0,0,2,0,2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  2,0,0,0,0,2,2,2,0,0,2,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};


SequenceModel Windows1252_SpanishModel =
{
  Windows1252CharToOrderMap,
  SpanishLangModel,
  34,
  (float)0.9966324196921269,
  PR_TRUE,
  "windows-1252"
};

SequenceModel Latin1_SpanishModel =
{
  Latin1CharToOrderMap,
  SpanishLangModel,
  34,
  (float)0.9966324196921269,
  PR_TRUE,
  "ISO-8859-1"
};

SequenceModel Latin15_SpanishModel =
{
  Latin15CharToOrderMap,
  SpanishLangModel,
  34,
  (float)0.9966324196921269,
  PR_TRUE,
  "ISO-8859-15"
};
