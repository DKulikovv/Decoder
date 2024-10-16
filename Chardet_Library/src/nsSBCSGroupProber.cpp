/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * vim: et sw=2 ts=2 fdm=marker
 */
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
 *          Shy Shalom <shooshX@gmail.com>
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

#include <stdio.h>
#include "prmem.h"

#include "nsSBCharSetProber.h"
#include "nsSBCSGroupProber.h"

#include "nsHebrewProber.h"

nsSBCSGroupProber::nsSBCSGroupProber()
{
  mProbers[0] = new nsSingleByteCharSetProber(&Win1251_CyrillicModel);
  mProbers[1] = new nsSingleByteCharSetProber(&Koi8r_CyrillicModel);
  mProbers[2] = new nsSingleByteCharSetProber(&Latin5_CyrillicModel);
  mProbers[3] = new nsSingleByteCharSetProber(&MacCyrillicModel);
  mProbers[4] = new nsSingleByteCharSetProber(&Ibm866_CyrillicModel);
  mProbers[5] = new nsSingleByteCharSetProber(&Ibm855_CyrillicModel);
  mProbers[6] = new nsSingleByteCharSetProber(&Latin7_GreekModel);
  mProbers[7] = new nsSingleByteCharSetProber(&Win1253_GreekModel);
  mProbers[8] = new nsSingleByteCharSetProber(&Latin5_BulgarianModel);
  mProbers[9] = new nsSingleByteCharSetProber(&Win1251_BulgarianModel);

  nsHebrewProber *hebprober = new nsHebrewProber();
  // Notice: Any change in these indexes - 10,11,12 must be reflected
  // in the code below as well.
  mProbers[10] = hebprober;
  mProbers[11] = new nsSingleByteCharSetProber(&Win1255_HebrewModel, PR_FALSE, hebprober); // Logical Hebrew
  mProbers[12] = new nsSingleByteCharSetProber(&Win1255_HebrewModel, PR_TRUE, hebprober); // Visual Hebrew
  // Tell the Hebrew prober about the logical and visual probers
  if (mProbers[10] && mProbers[11] && mProbers[12]) // all are not null
  {
    hebprober->SetModelProbers(mProbers[11], mProbers[12]);
  }
  else // One or more is null. avoid any Hebrew probing, null them all
  {
    for (unsigned i = 10; i <= 12; ++i)
    {
      delete mProbers[i];
      mProbers[i] = 0;
    }
  }

  mProbers[13] = new nsSingleByteCharSetProber(&Latin2_HungarianModel);
  mProbers[14] = new nsSingleByteCharSetProber(&Win1250_HungarianModel);
  mProbers[15] = new nsSingleByteCharSetProber(&TIS620_ThaiModel);
  mProbers[16] = new nsSingleByteCharSetProber(&Latin11_ThaiModel);

  mProbers[17] = new nsSingleByteCharSetProber(&Latin6_ArabicModel);
  mProbers[18] = new nsSingleByteCharSetProber(&Windows1256_ArabicModel);

  mProbers[19] = new nsSingleByteCharSetProber(&Latin15_DanishModel);
  mProbers[20] = new nsSingleByteCharSetProber(&Latin1_DanishModel);
  mProbers[21] = new nsSingleByteCharSetProber(&Windows1252_DanishModel);

  mProbers[22] = new nsSingleByteCharSetProber(&Latin3_EsperantoModel);

  mProbers[23] = new nsSingleByteCharSetProber(&Latin1_FrenchModel);
  mProbers[24] = new nsSingleByteCharSetProber(&Latin15_FrenchModel);
  mProbers[25] = new nsSingleByteCharSetProber(&Windows1252_FrenchModel);

  mProbers[26] = new nsSingleByteCharSetProber(&Latin1_GermanModel);
  mProbers[27] = new nsSingleByteCharSetProber(&Windows1252_GermanModel);

  mProbers[28] = new nsSingleByteCharSetProber(&Latin1_SpanishModel);
  mProbers[29] = new nsSingleByteCharSetProber(&Latin15_SpanishModel);
  mProbers[30] = new nsSingleByteCharSetProber(&Windows1252_SpanishModel);

  mProbers[31] = new nsSingleByteCharSetProber(&Latin3_TurkishModel);
  mProbers[32] = new nsSingleByteCharSetProber(&Latin9_TurkishModel);

  mProbers[33] = new nsSingleByteCharSetProber(&Viscii_VietnameseModel);
  mProbers[34] = new nsSingleByteCharSetProber(&Windows1258_VietnameseModel);

  Reset();
}

nsSBCSGroupProber::~nsSBCSGroupProber()
{
  for (unsigned i = 0; i < NUM_OF_SBCS_PROBERS; i++)
  {
    delete mProbers[i];
  }
}


const char* nsSBCSGroupProber::GetCharSetName()
{
  //if we have no answer yet
  if (mBestGuess == -1)
  {
    GetConfidence();
    //no charset seems positive
    if (mBestGuess == -1)
      //we will use default.
      mBestGuess = 0;
  }
  return mProbers[mBestGuess]->GetCharSetName();
}

void  nsSBCSGroupProber::Reset(void)
{
  mActiveNum = 0;
  for (unsigned i = 0; i < NUM_OF_SBCS_PROBERS; i++)
  {
    if (mProbers[i]) // not null
    {
      mProbers[i]->Reset();
      mIsActive[i] = PR_TRUE;
      ++mActiveNum;
    }
    else
      mIsActive[i] = PR_FALSE;
  }
  mBestGuess = -1;
  mState = eDetecting;
}


nsProbingState nsSBCSGroupProber::HandleData(const char* aBuf, unsigned aLen)
{
  nsProbingState st;
  unsigned i;
  char *newBuf1 = 0;
  unsigned newLen1 = 0;

  //apply filter to original buffer, and we got new buffer back
  //depend on what script it is, we will feed them the new buffer
  //we got after applying proper filter
  //this is done without any consideration to KeepEnglishLetters
  //of each prober since as of now, there are no probers here which
  //recognize languages with English characters.
  if (!FilterWithoutEnglishLetters(aBuf, aLen, &newBuf1, newLen1))
    goto done;

  if (newLen1 == 0)
    goto done; // Nothing to see here, move on.

  for (i = 0; i < NUM_OF_SBCS_PROBERS; i++)
  {
     if (!mIsActive[i])
       continue;
     st = mProbers[i]->HandleData(newBuf1, newLen1);
     if (st == eFoundIt)
     {
       mBestGuess = i;
       mState = eFoundIt;
       break;
     }
     else if (st == eNotMe)
     {
       mIsActive[i] = PR_FALSE;
       mActiveNum--;
       if (mActiveNum <= 0)
       {
         mState = eNotMe;
         break;
       }
     }
  }

done:
  PR_FREEIF(newBuf1);

  return mState;
}

float nsSBCSGroupProber::GetConfidence(void)
{
  unsigned i;
  float bestConf = 0.0, cf;

  switch (mState)
  {
  case eFoundIt:
    return (float)0.99; //sure yes
  case eNotMe:
    return (float)0.01;  //sure no
  default:
    for (i = 0; i < NUM_OF_SBCS_PROBERS; i++)
    {
      if (!mIsActive[i])
        continue;
      cf = mProbers[i]->GetConfidence();
      if (bestConf < cf)
      {
        bestConf = cf;
        mBestGuess = i;
      }
    }
  }
  return bestConf;
}

#ifdef DEBUG_chardet
void nsSBCSGroupProber::DumpStatus()
{
  unsigned i;
  float cf;

  cf = GetConfidence();
  printf(" SBCS Group Prober --------begin status \r\n");
  for (i = 0; i < NUM_OF_SBCS_PROBERS; i++)
  {
    if (!mIsActive[i])
      printf("  inactive: [%s] (i.e. confidence is too low).\r\n", mProbers[i]->GetCharSetName());
    else
      mProbers[i]->DumpStatus();
  }
  printf(" SBCS Group found best match [%s] confidence %f.\r\n",
         mProbers[mBestGuess]->GetCharSetName(), cf);
}
#endif
