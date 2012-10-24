/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

/**
 * @file countriesmodel.cpp
 * @short Implementation of PublicTransportation::Gui::CountriesModel
 */

#include "countriesmodel.h"

namespace PublicTransportation
{

namespace Gui
{

/**
 * @internal
 * @brief Private class used in PublicTransportation::Gui::CountriesModel
 */
struct CountriesModelItem
{
    /**
     * @internal
     * @short Name
     */
    QString name;
    /**
     * @internal
     * @short ISO code
     */
    QString isoCode;
};

/**
 * @internal
 * @short Private class for PublicTransportation::Gui::CountriesModel
 */
class CountriesModelPrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    CountriesModelPrivate();
    /**
     * @internal
     * @short Unaccent strings
     *
     * @param string string to unaccent.
     * @return unaccented string.
     */
    static QString unaccent(const QString &string);
    /**
     * @internal
     * @short Filter
     */
    QString filter;
    /**
     * @internal
     * @short Current
     */
    CountriesModelItem *current;
    /**
     * @internal
     * @short Countries
     */
    QList<CountriesModelItem *> data;
    /**
     * @internal
     * @short All
     */
    CountriesModelItem *all;
    /**
     * @internal
     * @short Countries
     */
    QList<CountriesModelItem *> countries;
};

CountriesModelPrivate::CountriesModelPrivate()
{
    all = new CountriesModelItem;
    all->name = QObject::tr("All countries");
    all->isoCode = QString();
    current = all;

    CountriesModelItem *itemAF = new CountriesModelItem;
    itemAF->name = QObject::trUtf8("Afghanistan");
    itemAF->isoCode = "AF";
    countries.append(itemAF);
    CountriesModelItem *itemAX = new CountriesModelItem;
    itemAX->name = QObject::trUtf8("Åland Islands");
    itemAX->isoCode = "AX";
    countries.append(itemAX);
    CountriesModelItem *itemAL = new CountriesModelItem;
    itemAL->name = QObject::trUtf8("Albania");
    itemAL->isoCode = "AL";
    countries.append(itemAL);
    CountriesModelItem *itemDZ = new CountriesModelItem;
    itemDZ->name = QObject::trUtf8("Algeria");
    itemDZ->isoCode = "DZ";
    countries.append(itemDZ);
    CountriesModelItem *itemAS = new CountriesModelItem;
    itemAS->name = QObject::trUtf8("American Samoa");
    itemAS->isoCode = "AS";
    countries.append(itemAS);
    CountriesModelItem *itemAD = new CountriesModelItem;
    itemAD->name = QObject::trUtf8("Andorra");
    itemAD->isoCode = "AD";
    countries.append(itemAD);
    CountriesModelItem *itemAO = new CountriesModelItem;
    itemAO->name = QObject::trUtf8("Angola");
    itemAO->isoCode = "AO";
    countries.append(itemAO);
    CountriesModelItem *itemAI = new CountriesModelItem;
    itemAI->name = QObject::trUtf8("Anguilla");
    itemAI->isoCode = "AI";
    countries.append(itemAI);
    CountriesModelItem *itemAQ = new CountriesModelItem;
    itemAQ->name = QObject::trUtf8("Antarctica");
    itemAQ->isoCode = "AQ";
    countries.append(itemAQ);
    CountriesModelItem *itemAG = new CountriesModelItem;
    itemAG->name = QObject::trUtf8("Antigua and Barbuda");
    itemAG->isoCode = "AG";
    countries.append(itemAG);
    CountriesModelItem *itemAR = new CountriesModelItem;
    itemAR->name = QObject::trUtf8("Argentina");
    itemAR->isoCode = "AR";
    countries.append(itemAR);
    CountriesModelItem *itemAM = new CountriesModelItem;
    itemAM->name = QObject::trUtf8("Armenia");
    itemAM->isoCode = "AM";
    countries.append(itemAM);
    CountriesModelItem *itemAW = new CountriesModelItem;
    itemAW->name = QObject::trUtf8("Aruba");
    itemAW->isoCode = "AW";
    countries.append(itemAW);
    CountriesModelItem *itemAU = new CountriesModelItem;
    itemAU->name = QObject::trUtf8("Australia");
    itemAU->isoCode = "AU";
    countries.append(itemAU);
    CountriesModelItem *itemAT = new CountriesModelItem;
    itemAT->name = QObject::trUtf8("Austria");
    itemAT->isoCode = "AT";
    countries.append(itemAT);
    CountriesModelItem *itemAZ = new CountriesModelItem;
    itemAZ->name = QObject::trUtf8("Azerbaijan");
    itemAZ->isoCode = "AZ";
    countries.append(itemAZ);
    CountriesModelItem *itemBS = new CountriesModelItem;
    itemBS->name = QObject::trUtf8("Bahamas");
    itemBS->isoCode = "BS";
    countries.append(itemBS);
    CountriesModelItem *itemBH = new CountriesModelItem;
    itemBH->name = QObject::trUtf8("Bahrain");
    itemBH->isoCode = "BH";
    countries.append(itemBH);
    CountriesModelItem *itemBD = new CountriesModelItem;
    itemBD->name = QObject::trUtf8("Bangladesh");
    itemBD->isoCode = "BD";
    countries.append(itemBD);
    CountriesModelItem *itemBB = new CountriesModelItem;
    itemBB->name = QObject::trUtf8("Barbados");
    itemBB->isoCode = "BB";
    countries.append(itemBB);
    CountriesModelItem *itemBY = new CountriesModelItem;
    itemBY->name = QObject::trUtf8("Belarus");
    itemBY->isoCode = "BY";
    countries.append(itemBY);
    CountriesModelItem *itemBE = new CountriesModelItem;
    itemBE->name = QObject::trUtf8("Belgium");
    itemBE->isoCode = "BE";
    countries.append(itemBE);
    CountriesModelItem *itemBZ = new CountriesModelItem;
    itemBZ->name = QObject::trUtf8("Belize");
    itemBZ->isoCode = "BZ";
    countries.append(itemBZ);
    CountriesModelItem *itemBJ = new CountriesModelItem;
    itemBJ->name = QObject::trUtf8("Benin");
    itemBJ->isoCode = "BJ";
    countries.append(itemBJ);
    CountriesModelItem *itemBM = new CountriesModelItem;
    itemBM->name = QObject::trUtf8("Bermuda");
    itemBM->isoCode = "BM";
    countries.append(itemBM);
    CountriesModelItem *itemBT = new CountriesModelItem;
    itemBT->name = QObject::trUtf8("Bhutan");
    itemBT->isoCode = "BT";
    countries.append(itemBT);
    CountriesModelItem *itemBO = new CountriesModelItem;
    itemBO->name = QObject::trUtf8("Bolivia");
    itemBO->isoCode = "BO";
    countries.append(itemBO);
    CountriesModelItem *itemBA = new CountriesModelItem;
    itemBA->name = QObject::trUtf8("Bosnia and Herzegovina");
    itemBA->isoCode = "BA";
    countries.append(itemBA);
    CountriesModelItem *itemBW = new CountriesModelItem;
    itemBW->name = QObject::trUtf8("Botswana");
    itemBW->isoCode = "BW";
    countries.append(itemBW);
    CountriesModelItem *itemBV = new CountriesModelItem;
    itemBV->name = QObject::trUtf8("Bouvet Island");
    itemBV->isoCode = "BV";
    countries.append(itemBV);
    CountriesModelItem *itemBR = new CountriesModelItem;
    itemBR->name = QObject::trUtf8("Brazil");
    itemBR->isoCode = "BR";
    countries.append(itemBR);
    CountriesModelItem *itemIO = new CountriesModelItem;
    itemIO->name = QObject::trUtf8("British Indian Ocean Territory");
    itemIO->isoCode = "IO";
    countries.append(itemIO);
    CountriesModelItem *itemBN = new CountriesModelItem;
    itemBN->name = QObject::trUtf8("Brunei Darussalam");
    itemBN->isoCode = "BN";
    countries.append(itemBN);
    CountriesModelItem *itemBG = new CountriesModelItem;
    itemBG->name = QObject::trUtf8("Bulgaria");
    itemBG->isoCode = "BG";
    countries.append(itemBG);
    CountriesModelItem *itemBF = new CountriesModelItem;
    itemBF->name = QObject::trUtf8("Burkina Faso");
    itemBF->isoCode = "BF";
    countries.append(itemBF);
    CountriesModelItem *itemBI = new CountriesModelItem;
    itemBI->name = QObject::trUtf8("Burundi");
    itemBI->isoCode = "BI";
    countries.append(itemBI);
    CountriesModelItem *itemKH = new CountriesModelItem;
    itemKH->name = QObject::trUtf8("Cambodia");
    itemKH->isoCode = "KH";
    countries.append(itemKH);
    CountriesModelItem *itemCM = new CountriesModelItem;
    itemCM->name = QObject::trUtf8("Cameroon");
    itemCM->isoCode = "CM";
    countries.append(itemCM);
    CountriesModelItem *itemCA = new CountriesModelItem;
    itemCA->name = QObject::trUtf8("Canada");
    itemCA->isoCode = "CA";
    countries.append(itemCA);
    CountriesModelItem *itemCV = new CountriesModelItem;
    itemCV->name = QObject::trUtf8("Cape Verde");
    itemCV->isoCode = "CV";
    countries.append(itemCV);
    CountriesModelItem *itemKY = new CountriesModelItem;
    itemKY->name = QObject::trUtf8("Cayman Islands");
    itemKY->isoCode = "KY";
    countries.append(itemKY);
    CountriesModelItem *itemCF = new CountriesModelItem;
    itemCF->name = QObject::trUtf8("Central African Republic");
    itemCF->isoCode = "CF";
    countries.append(itemCF);
    CountriesModelItem *itemTD = new CountriesModelItem;
    itemTD->name = QObject::trUtf8("Chad");
    itemTD->isoCode = "TD";
    countries.append(itemTD);
    CountriesModelItem *itemCL = new CountriesModelItem;
    itemCL->name = QObject::trUtf8("Chile");
    itemCL->isoCode = "CL";
    countries.append(itemCL);
    CountriesModelItem *itemCN = new CountriesModelItem;
    itemCN->name = QObject::trUtf8("China");
    itemCN->isoCode = "CN";
    countries.append(itemCN);
    CountriesModelItem *itemCX = new CountriesModelItem;
    itemCX->name = QObject::trUtf8("Christmas Island");
    itemCX->isoCode = "CX";
    countries.append(itemCX);
    CountriesModelItem *itemCC = new CountriesModelItem;
    itemCC->name = QObject::trUtf8("Cocos (Keeling) Islands");
    itemCC->isoCode = "CC";
    countries.append(itemCC);
    CountriesModelItem *itemCO = new CountriesModelItem;
    itemCO->name = QObject::trUtf8("Colombia");
    itemCO->isoCode = "CO";
    countries.append(itemCO);
    CountriesModelItem *itemKM = new CountriesModelItem;
    itemKM->name = QObject::trUtf8("Comoros");
    itemKM->isoCode = "KM";
    countries.append(itemKM);
    CountriesModelItem *itemCG = new CountriesModelItem;
    itemCG->name = QObject::trUtf8("Congo");
    itemCG->isoCode = "CG";
    countries.append(itemCG);
    CountriesModelItem *itemCD = new CountriesModelItem;
    itemCD->name = QObject::trUtf8("Congo, The Democratic Republic of The");
    itemCD->isoCode = "CD";
    countries.append(itemCD);
    CountriesModelItem *itemCK = new CountriesModelItem;
    itemCK->name = QObject::trUtf8("Cook Islands");
    itemCK->isoCode = "CK";
    countries.append(itemCK);
    CountriesModelItem *itemCR = new CountriesModelItem;
    itemCR->name = QObject::trUtf8("Costa Rica");
    itemCR->isoCode = "CR";
    countries.append(itemCR);
    CountriesModelItem *itemCI = new CountriesModelItem;
    itemCI->name = QObject::trUtf8("Cote D'ivoire");
    itemCI->isoCode = "CI";
    countries.append(itemCI);
    CountriesModelItem *itemHR = new CountriesModelItem;
    itemHR->name = QObject::trUtf8("Croatia");
    itemHR->isoCode = "HR";
    countries.append(itemHR);
    CountriesModelItem *itemCU = new CountriesModelItem;
    itemCU->name = QObject::trUtf8("Cuba");
    itemCU->isoCode = "CU";
    countries.append(itemCU);
    CountriesModelItem *itemCY = new CountriesModelItem;
    itemCY->name = QObject::trUtf8("Cyprus");
    itemCY->isoCode = "CY";
    countries.append(itemCY);
    CountriesModelItem *itemCZ = new CountriesModelItem;
    itemCZ->name = QObject::trUtf8("Czech Republic");
    itemCZ->isoCode = "CZ";
    countries.append(itemCZ);
    CountriesModelItem *itemDK = new CountriesModelItem;
    itemDK->name = QObject::trUtf8("Denmark");
    itemDK->isoCode = "DK";
    countries.append(itemDK);
    CountriesModelItem *itemDJ = new CountriesModelItem;
    itemDJ->name = QObject::trUtf8("Djibouti");
    itemDJ->isoCode = "DJ";
    countries.append(itemDJ);
    CountriesModelItem *itemDM = new CountriesModelItem;
    itemDM->name = QObject::trUtf8("Dominica");
    itemDM->isoCode = "DM";
    countries.append(itemDM);
    CountriesModelItem *itemDO = new CountriesModelItem;
    itemDO->name = QObject::trUtf8("Dominican Republic");
    itemDO->isoCode = "DO";
    countries.append(itemDO);
    CountriesModelItem *itemEC = new CountriesModelItem;
    itemEC->name = QObject::trUtf8("Ecuador");
    itemEC->isoCode = "EC";
    countries.append(itemEC);
    CountriesModelItem *itemEG = new CountriesModelItem;
    itemEG->name = QObject::trUtf8("Egypt");
    itemEG->isoCode = "EG";
    countries.append(itemEG);
    CountriesModelItem *itemSV = new CountriesModelItem;
    itemSV->name = QObject::trUtf8("El Salvador");
    itemSV->isoCode = "SV";
    countries.append(itemSV);
    CountriesModelItem *itemGQ = new CountriesModelItem;
    itemGQ->name = QObject::trUtf8("Equatorial Guinea");
    itemGQ->isoCode = "GQ";
    countries.append(itemGQ);
    CountriesModelItem *itemER = new CountriesModelItem;
    itemER->name = QObject::trUtf8("Eritrea");
    itemER->isoCode = "ER";
    countries.append(itemER);
    CountriesModelItem *itemEE = new CountriesModelItem;
    itemEE->name = QObject::trUtf8("Estonia");
    itemEE->isoCode = "EE";
    countries.append(itemEE);
    CountriesModelItem *itemET = new CountriesModelItem;
    itemET->name = QObject::trUtf8("Ethiopia");
    itemET->isoCode = "ET";
    countries.append(itemET);
    CountriesModelItem *itemFK = new CountriesModelItem;
    itemFK->name = QObject::trUtf8("Falkland Islands (Malvinas)");
    itemFK->isoCode = "FK";
    countries.append(itemFK);
    CountriesModelItem *itemFO = new CountriesModelItem;
    itemFO->name = QObject::trUtf8("Faroe Islands");
    itemFO->isoCode = "FO";
    countries.append(itemFO);
    CountriesModelItem *itemFJ = new CountriesModelItem;
    itemFJ->name = QObject::trUtf8("Fiji");
    itemFJ->isoCode = "FJ";
    countries.append(itemFJ);
    CountriesModelItem *itemFI = new CountriesModelItem;
    itemFI->name = QObject::trUtf8("Finland");
    itemFI->isoCode = "FI";
    countries.append(itemFI);
    CountriesModelItem *itemFR = new CountriesModelItem;
    itemFR->name = QObject::trUtf8("France");
    itemFR->isoCode = "FR";
    countries.append(itemFR);
    CountriesModelItem *itemGF = new CountriesModelItem;
    itemGF->name = QObject::trUtf8("French Guiana");
    itemGF->isoCode = "GF";
    countries.append(itemGF);
    CountriesModelItem *itemPF = new CountriesModelItem;
    itemPF->name = QObject::trUtf8("French Polynesia");
    itemPF->isoCode = "PF";
    countries.append(itemPF);
    CountriesModelItem *itemTF = new CountriesModelItem;
    itemTF->name = QObject::trUtf8("French Southern Territories");
    itemTF->isoCode = "TF";
    countries.append(itemTF);
    CountriesModelItem *itemGA = new CountriesModelItem;
    itemGA->name = QObject::trUtf8("Gabon");
    itemGA->isoCode = "GA";
    countries.append(itemGA);
    CountriesModelItem *itemGM = new CountriesModelItem;
    itemGM->name = QObject::trUtf8("Gambia");
    itemGM->isoCode = "GM";
    countries.append(itemGM);
    CountriesModelItem *itemGE = new CountriesModelItem;
    itemGE->name = QObject::trUtf8("Georgia");
    itemGE->isoCode = "GE";
    countries.append(itemGE);
    CountriesModelItem *itemDE = new CountriesModelItem;
    itemDE->name = QObject::trUtf8("Germany");
    itemDE->isoCode = "DE";
    countries.append(itemDE);
    CountriesModelItem *itemGH = new CountriesModelItem;
    itemGH->name = QObject::trUtf8("Ghana");
    itemGH->isoCode = "GH";
    countries.append(itemGH);
    CountriesModelItem *itemGI = new CountriesModelItem;
    itemGI->name = QObject::trUtf8("Gibraltar");
    itemGI->isoCode = "GI";
    countries.append(itemGI);
    CountriesModelItem *itemGR = new CountriesModelItem;
    itemGR->name = QObject::trUtf8("Greece");
    itemGR->isoCode = "GR";
    countries.append(itemGR);
    CountriesModelItem *itemGL = new CountriesModelItem;
    itemGL->name = QObject::trUtf8("Greenland");
    itemGL->isoCode = "GL";
    countries.append(itemGL);
    CountriesModelItem *itemGD = new CountriesModelItem;
    itemGD->name = QObject::trUtf8("Grenada");
    itemGD->isoCode = "GD";
    countries.append(itemGD);
    CountriesModelItem *itemGP = new CountriesModelItem;
    itemGP->name = QObject::trUtf8("Guadeloupe");
    itemGP->isoCode = "GP";
    countries.append(itemGP);
    CountriesModelItem *itemGU = new CountriesModelItem;
    itemGU->name = QObject::trUtf8("Guam");
    itemGU->isoCode = "GU";
    countries.append(itemGU);
    CountriesModelItem *itemGT = new CountriesModelItem;
    itemGT->name = QObject::trUtf8("Guatemala");
    itemGT->isoCode = "GT";
    countries.append(itemGT);
    CountriesModelItem *itemGG = new CountriesModelItem;
    itemGG->name = QObject::trUtf8("Guernsey");
    itemGG->isoCode = "GG";
    countries.append(itemGG);
    CountriesModelItem *itemGN = new CountriesModelItem;
    itemGN->name = QObject::trUtf8("Guinea");
    itemGN->isoCode = "GN";
    countries.append(itemGN);
    CountriesModelItem *itemGW = new CountriesModelItem;
    itemGW->name = QObject::trUtf8("Guinea-bissau");
    itemGW->isoCode = "GW";
    countries.append(itemGW);
    CountriesModelItem *itemGY = new CountriesModelItem;
    itemGY->name = QObject::trUtf8("Guyana");
    itemGY->isoCode = "GY";
    countries.append(itemGY);
    CountriesModelItem *itemHT = new CountriesModelItem;
    itemHT->name = QObject::trUtf8("Haiti");
    itemHT->isoCode = "HT";
    countries.append(itemHT);
    CountriesModelItem *itemHM = new CountriesModelItem;
    itemHM->name = QObject::trUtf8("Heard Island and Mcdonald Islands");
    itemHM->isoCode = "HM";
    countries.append(itemHM);
    CountriesModelItem *itemVA = new CountriesModelItem;
    itemVA->name = QObject::trUtf8("Holy See (Vatican City State)");
    itemVA->isoCode = "VA";
    countries.append(itemVA);
    CountriesModelItem *itemHN = new CountriesModelItem;
    itemHN->name = QObject::trUtf8("Honduras");
    itemHN->isoCode = "HN";
    countries.append(itemHN);
    CountriesModelItem *itemHK = new CountriesModelItem;
    itemHK->name = QObject::trUtf8("Hong Kong");
    itemHK->isoCode = "HK";
    countries.append(itemHK);
    CountriesModelItem *itemHU = new CountriesModelItem;
    itemHU->name = QObject::trUtf8("Hungary");
    itemHU->isoCode = "HU";
    countries.append(itemHU);
    CountriesModelItem *itemIS = new CountriesModelItem;
    itemIS->name = QObject::trUtf8("Iceland");
    itemIS->isoCode = "IS";
    countries.append(itemIS);
    CountriesModelItem *itemIN = new CountriesModelItem;
    itemIN->name = QObject::trUtf8("India");
    itemIN->isoCode = "IN";
    countries.append(itemIN);
    CountriesModelItem *itemID = new CountriesModelItem;
    itemID->name = QObject::trUtf8("Indonesia");
    itemID->isoCode = "ID";
    countries.append(itemID);
    CountriesModelItem *itemIR = new CountriesModelItem;
    itemIR->name = QObject::trUtf8("Iran, Islamic Republic of");
    itemIR->isoCode = "IR";
    countries.append(itemIR);
    CountriesModelItem *itemIQ = new CountriesModelItem;
    itemIQ->name = QObject::trUtf8("Iraq");
    itemIQ->isoCode = "IQ";
    countries.append(itemIQ);
    CountriesModelItem *itemIE = new CountriesModelItem;
    itemIE->name = QObject::trUtf8("Ireland");
    itemIE->isoCode = "IE";
    countries.append(itemIE);
    CountriesModelItem *itemIM = new CountriesModelItem;
    itemIM->name = QObject::trUtf8("Isle of Man");
    itemIM->isoCode = "IM";
    countries.append(itemIM);
    CountriesModelItem *itemIL = new CountriesModelItem;
    itemIL->name = QObject::trUtf8("Israel");
    itemIL->isoCode = "IL";
    countries.append(itemIL);
    CountriesModelItem *itemIT = new CountriesModelItem;
    itemIT->name = QObject::trUtf8("Italy");
    itemIT->isoCode = "IT";
    countries.append(itemIT);
    CountriesModelItem *itemJM = new CountriesModelItem;
    itemJM->name = QObject::trUtf8("Jamaica");
    itemJM->isoCode = "JM";
    countries.append(itemJM);
    CountriesModelItem *itemJP = new CountriesModelItem;
    itemJP->name = QObject::trUtf8("Japan");
    itemJP->isoCode = "JP";
    countries.append(itemJP);
    CountriesModelItem *itemJE = new CountriesModelItem;
    itemJE->name = QObject::trUtf8("Jersey");
    itemJE->isoCode = "JE";
    countries.append(itemJE);
    CountriesModelItem *itemJO = new CountriesModelItem;
    itemJO->name = QObject::trUtf8("Jordan");
    itemJO->isoCode = "JO";
    countries.append(itemJO);
    CountriesModelItem *itemKZ = new CountriesModelItem;
    itemKZ->name = QObject::trUtf8("Kazakhstan");
    itemKZ->isoCode = "KZ";
    countries.append(itemKZ);
    CountriesModelItem *itemKE = new CountriesModelItem;
    itemKE->name = QObject::trUtf8("Kenya");
    itemKE->isoCode = "KE";
    countries.append(itemKE);
    CountriesModelItem *itemKI = new CountriesModelItem;
    itemKI->name = QObject::trUtf8("Kiribati");
    itemKI->isoCode = "KI";
    countries.append(itemKI);
    CountriesModelItem *itemKP = new CountriesModelItem;
    itemKP->name = QObject::trUtf8("Korea, Democratic People's Republic of");
    itemKP->isoCode = "KP";
    countries.append(itemKP);
    CountriesModelItem *itemKR = new CountriesModelItem;
    itemKR->name = QObject::trUtf8("Korea, Republic of");
    itemKR->isoCode = "KR";
    countries.append(itemKR);
    CountriesModelItem *itemKW = new CountriesModelItem;
    itemKW->name = QObject::trUtf8("Kuwait");
    itemKW->isoCode = "KW";
    countries.append(itemKW);
    CountriesModelItem *itemKG = new CountriesModelItem;
    itemKG->name = QObject::trUtf8("Kyrgyzstan");
    itemKG->isoCode = "KG";
    countries.append(itemKG);
    CountriesModelItem *itemLA = new CountriesModelItem;
    itemLA->name = QObject::trUtf8("Lao People's Democratic Republic");
    itemLA->isoCode = "LA";
    countries.append(itemLA);
    CountriesModelItem *itemLV = new CountriesModelItem;
    itemLV->name = QObject::trUtf8("Latvia");
    itemLV->isoCode = "LV";
    countries.append(itemLV);
    CountriesModelItem *itemLB = new CountriesModelItem;
    itemLB->name = QObject::trUtf8("Lebanon");
    itemLB->isoCode = "LB";
    countries.append(itemLB);
    CountriesModelItem *itemLS = new CountriesModelItem;
    itemLS->name = QObject::trUtf8("Lesotho");
    itemLS->isoCode = "LS";
    countries.append(itemLS);
    CountriesModelItem *itemLR = new CountriesModelItem;
    itemLR->name = QObject::trUtf8("Liberia");
    itemLR->isoCode = "LR";
    countries.append(itemLR);
    CountriesModelItem *itemLY = new CountriesModelItem;
    itemLY->name = QObject::trUtf8("Libyan Arab Jamahiriya");
    itemLY->isoCode = "LY";
    countries.append(itemLY);
    CountriesModelItem *itemLI = new CountriesModelItem;
    itemLI->name = QObject::trUtf8("Liechtenstein");
    itemLI->isoCode = "LI";
    countries.append(itemLI);
    CountriesModelItem *itemLT = new CountriesModelItem;
    itemLT->name = QObject::trUtf8("Lithuania");
    itemLT->isoCode = "LT";
    countries.append(itemLT);
    CountriesModelItem *itemLU = new CountriesModelItem;
    itemLU->name = QObject::trUtf8("Luxembourg");
    itemLU->isoCode = "LU";
    countries.append(itemLU);
    CountriesModelItem *itemMO = new CountriesModelItem;
    itemMO->name = QObject::trUtf8("Macao");
    itemMO->isoCode = "MO";
    countries.append(itemMO);
    CountriesModelItem *itemMK = new CountriesModelItem;
    itemMK->name = QObject::trUtf8("Macedonia, The Former Yugoslav Republic of");
    itemMK->isoCode = "MK";
    countries.append(itemMK);
    CountriesModelItem *itemMG = new CountriesModelItem;
    itemMG->name = QObject::trUtf8("Madagascar");
    itemMG->isoCode = "MG";
    countries.append(itemMG);
    CountriesModelItem *itemMW = new CountriesModelItem;
    itemMW->name = QObject::trUtf8("Malawi");
    itemMW->isoCode = "MW";
    countries.append(itemMW);
    CountriesModelItem *itemMY = new CountriesModelItem;
    itemMY->name = QObject::trUtf8("Malaysia");
    itemMY->isoCode = "MY";
    countries.append(itemMY);
    CountriesModelItem *itemMV = new CountriesModelItem;
    itemMV->name = QObject::trUtf8("Maldives");
    itemMV->isoCode = "MV";
    countries.append(itemMV);
    CountriesModelItem *itemML = new CountriesModelItem;
    itemML->name = QObject::trUtf8("Mali");
    itemML->isoCode = "ML";
    countries.append(itemML);
    CountriesModelItem *itemMT = new CountriesModelItem;
    itemMT->name = QObject::trUtf8("Malta");
    itemMT->isoCode = "MT";
    countries.append(itemMT);
    CountriesModelItem *itemMH = new CountriesModelItem;
    itemMH->name = QObject::trUtf8("Marshall Islands");
    itemMH->isoCode = "MH";
    countries.append(itemMH);
    CountriesModelItem *itemMQ = new CountriesModelItem;
    itemMQ->name = QObject::trUtf8("Martinique");
    itemMQ->isoCode = "MQ";
    countries.append(itemMQ);
    CountriesModelItem *itemMR = new CountriesModelItem;
    itemMR->name = QObject::trUtf8("Mauritania");
    itemMR->isoCode = "MR";
    countries.append(itemMR);
    CountriesModelItem *itemMU = new CountriesModelItem;
    itemMU->name = QObject::trUtf8("Mauritius");
    itemMU->isoCode = "MU";
    countries.append(itemMU);
    CountriesModelItem *itemYT = new CountriesModelItem;
    itemYT->name = QObject::trUtf8("Mayotte");
    itemYT->isoCode = "YT";
    countries.append(itemYT);
    CountriesModelItem *itemMX = new CountriesModelItem;
    itemMX->name = QObject::trUtf8("Mexico");
    itemMX->isoCode = "MX";
    countries.append(itemMX);
    CountriesModelItem *itemFM = new CountriesModelItem;
    itemFM->name = QObject::trUtf8("Micronesia, Federated States of");
    itemFM->isoCode = "FM";
    countries.append(itemFM);
    CountriesModelItem *itemMD = new CountriesModelItem;
    itemMD->name = QObject::trUtf8("Moldova, Republic of");
    itemMD->isoCode = "MD";
    countries.append(itemMD);
    CountriesModelItem *itemMC = new CountriesModelItem;
    itemMC->name = QObject::trUtf8("Monaco");
    itemMC->isoCode = "MC";
    countries.append(itemMC);
    CountriesModelItem *itemMN = new CountriesModelItem;
    itemMN->name = QObject::trUtf8("Mongolia");
    itemMN->isoCode = "MN";
    countries.append(itemMN);
    CountriesModelItem *itemME = new CountriesModelItem;
    itemME->name = QObject::trUtf8("Montenegro");
    itemME->isoCode = "ME";
    countries.append(itemME);
    CountriesModelItem *itemMS = new CountriesModelItem;
    itemMS->name = QObject::trUtf8("Montserrat");
    itemMS->isoCode = "MS";
    countries.append(itemMS);
    CountriesModelItem *itemMA = new CountriesModelItem;
    itemMA->name = QObject::trUtf8("Morocco");
    itemMA->isoCode = "MA";
    countries.append(itemMA);
    CountriesModelItem *itemMZ = new CountriesModelItem;
    itemMZ->name = QObject::trUtf8("Mozambique");
    itemMZ->isoCode = "MZ";
    countries.append(itemMZ);
    CountriesModelItem *itemMM = new CountriesModelItem;
    itemMM->name = QObject::trUtf8("Myanmar");
    itemMM->isoCode = "MM";
    countries.append(itemMM);
    CountriesModelItem *itemNA = new CountriesModelItem;
    itemNA->name = QObject::trUtf8("Namibia");
    itemNA->isoCode = "NA";
    countries.append(itemNA);
    CountriesModelItem *itemNR = new CountriesModelItem;
    itemNR->name = QObject::trUtf8("Nauru");
    itemNR->isoCode = "NR";
    countries.append(itemNR);
    CountriesModelItem *itemNP = new CountriesModelItem;
    itemNP->name = QObject::trUtf8("Nepal");
    itemNP->isoCode = "NP";
    countries.append(itemNP);
    CountriesModelItem *itemNL = new CountriesModelItem;
    itemNL->name = QObject::trUtf8("Netherlands");
    itemNL->isoCode = "NL";
    countries.append(itemNL);
    CountriesModelItem *itemAN = new CountriesModelItem;
    itemAN->name = QObject::trUtf8("Netherlands Antilles");
    itemAN->isoCode = "AN";
    countries.append(itemAN);
    CountriesModelItem *itemNC = new CountriesModelItem;
    itemNC->name = QObject::trUtf8("New Caledonia");
    itemNC->isoCode = "NC";
    countries.append(itemNC);
    CountriesModelItem *itemNZ = new CountriesModelItem;
    itemNZ->name = QObject::trUtf8("New Zealand");
    itemNZ->isoCode = "NZ";
    countries.append(itemNZ);
    CountriesModelItem *itemNI = new CountriesModelItem;
    itemNI->name = QObject::trUtf8("Nicaragua");
    itemNI->isoCode = "NI";
    countries.append(itemNI);
    CountriesModelItem *itemNE = new CountriesModelItem;
    itemNE->name = QObject::trUtf8("Niger");
    itemNE->isoCode = "NE";
    countries.append(itemNE);
    CountriesModelItem *itemNG = new CountriesModelItem;
    itemNG->name = QObject::trUtf8("Nigeria");
    itemNG->isoCode = "NG";
    countries.append(itemNG);
    CountriesModelItem *itemNU = new CountriesModelItem;
    itemNU->name = QObject::trUtf8("Niue");
    itemNU->isoCode = "NU";
    countries.append(itemNU);
    CountriesModelItem *itemNF = new CountriesModelItem;
    itemNF->name = QObject::trUtf8("Norfolk Island");
    itemNF->isoCode = "NF";
    countries.append(itemNF);
    CountriesModelItem *itemMP = new CountriesModelItem;
    itemMP->name = QObject::trUtf8("Northern Mariana Islands");
    itemMP->isoCode = "MP";
    countries.append(itemMP);
    CountriesModelItem *itemNO = new CountriesModelItem;
    itemNO->name = QObject::trUtf8("Norway");
    itemNO->isoCode = "NO";
    countries.append(itemNO);
    CountriesModelItem *itemOM = new CountriesModelItem;
    itemOM->name = QObject::trUtf8("Oman");
    itemOM->isoCode = "OM";
    countries.append(itemOM);
    CountriesModelItem *itemPK = new CountriesModelItem;
    itemPK->name = QObject::trUtf8("Pakistan");
    itemPK->isoCode = "PK";
    countries.append(itemPK);
    CountriesModelItem *itemPW = new CountriesModelItem;
    itemPW->name = QObject::trUtf8("Palau");
    itemPW->isoCode = "PW";
    countries.append(itemPW);
    CountriesModelItem *itemPS = new CountriesModelItem;
    itemPS->name = QObject::trUtf8("Palestinian Territory, Occupied");
    itemPS->isoCode = "PS";
    countries.append(itemPS);
    CountriesModelItem *itemPA = new CountriesModelItem;
    itemPA->name = QObject::trUtf8("Panama");
    itemPA->isoCode = "PA";
    countries.append(itemPA);
    CountriesModelItem *itemPG = new CountriesModelItem;
    itemPG->name = QObject::trUtf8("Papua New Guinea");
    itemPG->isoCode = "PG";
    countries.append(itemPG);
    CountriesModelItem *itemPY = new CountriesModelItem;
    itemPY->name = QObject::trUtf8("Paraguay");
    itemPY->isoCode = "PY";
    countries.append(itemPY);
    CountriesModelItem *itemPE = new CountriesModelItem;
    itemPE->name = QObject::trUtf8("Peru");
    itemPE->isoCode = "PE";
    countries.append(itemPE);
    CountriesModelItem *itemPH = new CountriesModelItem;
    itemPH->name = QObject::trUtf8("Philippines");
    itemPH->isoCode = "PH";
    countries.append(itemPH);
    CountriesModelItem *itemPN = new CountriesModelItem;
    itemPN->name = QObject::trUtf8("Pitcairn");
    itemPN->isoCode = "PN";
    countries.append(itemPN);
    CountriesModelItem *itemPL = new CountriesModelItem;
    itemPL->name = QObject::trUtf8("Poland");
    itemPL->isoCode = "PL";
    countries.append(itemPL);
    CountriesModelItem *itemPT = new CountriesModelItem;
    itemPT->name = QObject::trUtf8("Portugal");
    itemPT->isoCode = "PT";
    countries.append(itemPT);
    CountriesModelItem *itemPR = new CountriesModelItem;
    itemPR->name = QObject::trUtf8("Puerto Rico");
    itemPR->isoCode = "PR";
    countries.append(itemPR);
    CountriesModelItem *itemQA = new CountriesModelItem;
    itemQA->name = QObject::trUtf8("Qatar");
    itemQA->isoCode = "QA";
    countries.append(itemQA);
    CountriesModelItem *itemRE = new CountriesModelItem;
    itemRE->name = QObject::trUtf8("Reunion");
    itemRE->isoCode = "RE";
    countries.append(itemRE);
    CountriesModelItem *itemRO = new CountriesModelItem;
    itemRO->name = QObject::trUtf8("Romania");
    itemRO->isoCode = "RO";
    countries.append(itemRO);
    CountriesModelItem *itemRU = new CountriesModelItem;
    itemRU->name = QObject::trUtf8("Russian Federation");
    itemRU->isoCode = "RU";
    countries.append(itemRU);
    CountriesModelItem *itemRW = new CountriesModelItem;
    itemRW->name = QObject::trUtf8("Rwanda");
    itemRW->isoCode = "RW";
    countries.append(itemRW);
    CountriesModelItem *itemSH = new CountriesModelItem;
    itemSH->name = QObject::trUtf8("Saint Helena");
    itemSH->isoCode = "SH";
    countries.append(itemSH);
    CountriesModelItem *itemKN = new CountriesModelItem;
    itemKN->name = QObject::trUtf8("Saint Kitts and Nevis");
    itemKN->isoCode = "KN";
    countries.append(itemKN);
    CountriesModelItem *itemLC = new CountriesModelItem;
    itemLC->name = QObject::trUtf8("Saint Lucia");
    itemLC->isoCode = "LC";
    countries.append(itemLC);
    CountriesModelItem *itemPM = new CountriesModelItem;
    itemPM->name = QObject::trUtf8("Saint Pierre and Miquelon");
    itemPM->isoCode = "PM";
    countries.append(itemPM);
    CountriesModelItem *itemVC = new CountriesModelItem;
    itemVC->name = QObject::trUtf8("Saint Vincent and The Grenadines");
    itemVC->isoCode = "VC";
    countries.append(itemVC);
    CountriesModelItem *itemWS = new CountriesModelItem;
    itemWS->name = QObject::trUtf8("Samoa");
    itemWS->isoCode = "WS";
    countries.append(itemWS);
    CountriesModelItem *itemSM = new CountriesModelItem;
    itemSM->name = QObject::trUtf8("San Marino");
    itemSM->isoCode = "SM";
    countries.append(itemSM);
    CountriesModelItem *itemST = new CountriesModelItem;
    itemST->name = QObject::trUtf8("Sao Tome and Principe");
    itemST->isoCode = "ST";
    countries.append(itemST);
    CountriesModelItem *itemSA = new CountriesModelItem;
    itemSA->name = QObject::trUtf8("Saudi Arabia");
    itemSA->isoCode = "SA";
    countries.append(itemSA);
    CountriesModelItem *itemSN = new CountriesModelItem;
    itemSN->name = QObject::trUtf8("Senegal");
    itemSN->isoCode = "SN";
    countries.append(itemSN);
    CountriesModelItem *itemRS = new CountriesModelItem;
    itemRS->name = QObject::trUtf8("Serbia");
    itemRS->isoCode = "RS";
    countries.append(itemRS);
    CountriesModelItem *itemSC = new CountriesModelItem;
    itemSC->name = QObject::trUtf8("Seychelles");
    itemSC->isoCode = "SC";
    countries.append(itemSC);
    CountriesModelItem *itemSL = new CountriesModelItem;
    itemSL->name = QObject::trUtf8("Sierra Leone");
    itemSL->isoCode = "SL";
    countries.append(itemSL);
    CountriesModelItem *itemSG = new CountriesModelItem;
    itemSG->name = QObject::trUtf8("Singapore");
    itemSG->isoCode = "SG";
    countries.append(itemSG);
    CountriesModelItem *itemSK = new CountriesModelItem;
    itemSK->name = QObject::trUtf8("Slovakia");
    itemSK->isoCode = "SK";
    countries.append(itemSK);
    CountriesModelItem *itemSI = new CountriesModelItem;
    itemSI->name = QObject::trUtf8("Slovenia");
    itemSI->isoCode = "SI";
    countries.append(itemSI);
    CountriesModelItem *itemSB = new CountriesModelItem;
    itemSB->name = QObject::trUtf8("Solomon Islands");
    itemSB->isoCode = "SB";
    countries.append(itemSB);
    CountriesModelItem *itemSO = new CountriesModelItem;
    itemSO->name = QObject::trUtf8("Somalia");
    itemSO->isoCode = "SO";
    countries.append(itemSO);
    CountriesModelItem *itemZA = new CountriesModelItem;
    itemZA->name = QObject::trUtf8("South Africa");
    itemZA->isoCode = "ZA";
    countries.append(itemZA);
    CountriesModelItem *itemGS = new CountriesModelItem;
    itemGS->name = QObject::trUtf8("South Georgia and The South Sandwich Islands");
    itemGS->isoCode = "GS";
    countries.append(itemGS);
    CountriesModelItem *itemES = new CountriesModelItem;
    itemES->name = QObject::trUtf8("Spain");
    itemES->isoCode = "ES";
    countries.append(itemES);
    CountriesModelItem *itemLK = new CountriesModelItem;
    itemLK->name = QObject::trUtf8("Sri Lanka");
    itemLK->isoCode = "LK";
    countries.append(itemLK);
    CountriesModelItem *itemSD = new CountriesModelItem;
    itemSD->name = QObject::trUtf8("Sudan");
    itemSD->isoCode = "SD";
    countries.append(itemSD);
    CountriesModelItem *itemSR = new CountriesModelItem;
    itemSR->name = QObject::trUtf8("Suriname");
    itemSR->isoCode = "SR";
    countries.append(itemSR);
    CountriesModelItem *itemSJ = new CountriesModelItem;
    itemSJ->name = QObject::trUtf8("Svalbard and Jan Mayen");
    itemSJ->isoCode = "SJ";
    countries.append(itemSJ);
    CountriesModelItem *itemSZ = new CountriesModelItem;
    itemSZ->name = QObject::trUtf8("Swaziland");
    itemSZ->isoCode = "SZ";
    countries.append(itemSZ);
    CountriesModelItem *itemSE = new CountriesModelItem;
    itemSE->name = QObject::trUtf8("Sweden");
    itemSE->isoCode = "SE";
    countries.append(itemSE);
    CountriesModelItem *itemCH = new CountriesModelItem;
    itemCH->name = QObject::trUtf8("Switzerland");
    itemCH->isoCode = "CH";
    countries.append(itemCH);
    CountriesModelItem *itemSY = new CountriesModelItem;
    itemSY->name = QObject::trUtf8("Syrian Arab Republic");
    itemSY->isoCode = "SY";
    countries.append(itemSY);
    CountriesModelItem *itemTW = new CountriesModelItem;
    itemTW->name = QObject::trUtf8("Taiwan, Province of China");
    itemTW->isoCode = "TW";
    countries.append(itemTW);
    CountriesModelItem *itemTJ = new CountriesModelItem;
    itemTJ->name = QObject::trUtf8("Tajikistan");
    itemTJ->isoCode = "TJ";
    countries.append(itemTJ);
    CountriesModelItem *itemTZ = new CountriesModelItem;
    itemTZ->name = QObject::trUtf8("Tanzania, United Republic of");
    itemTZ->isoCode = "TZ";
    countries.append(itemTZ);
    CountriesModelItem *itemTH = new CountriesModelItem;
    itemTH->name = QObject::trUtf8("Thailand");
    itemTH->isoCode = "TH";
    countries.append(itemTH);
    CountriesModelItem *itemTL = new CountriesModelItem;
    itemTL->name = QObject::trUtf8("Timor-leste");
    itemTL->isoCode = "TL";
    countries.append(itemTL);
    CountriesModelItem *itemTG = new CountriesModelItem;
    itemTG->name = QObject::trUtf8("Togo");
    itemTG->isoCode = "TG";
    countries.append(itemTG);
    CountriesModelItem *itemTK = new CountriesModelItem;
    itemTK->name = QObject::trUtf8("Tokelau");
    itemTK->isoCode = "TK";
    countries.append(itemTK);
    CountriesModelItem *itemTO = new CountriesModelItem;
    itemTO->name = QObject::trUtf8("Tonga");
    itemTO->isoCode = "TO";
    countries.append(itemTO);
    CountriesModelItem *itemTT = new CountriesModelItem;
    itemTT->name = QObject::trUtf8("Trinidad and Tobago");
    itemTT->isoCode = "TT";
    countries.append(itemTT);
    CountriesModelItem *itemTN = new CountriesModelItem;
    itemTN->name = QObject::trUtf8("Tunisia");
    itemTN->isoCode = "TN";
    countries.append(itemTN);
    CountriesModelItem *itemTR = new CountriesModelItem;
    itemTR->name = QObject::trUtf8("Turkey");
    itemTR->isoCode = "TR";
    countries.append(itemTR);
    CountriesModelItem *itemTM = new CountriesModelItem;
    itemTM->name = QObject::trUtf8("Turkmenistan");
    itemTM->isoCode = "TM";
    countries.append(itemTM);
    CountriesModelItem *itemTC = new CountriesModelItem;
    itemTC->name = QObject::trUtf8("Turks and Caicos Islands");
    itemTC->isoCode = "TC";
    countries.append(itemTC);
    CountriesModelItem *itemTV = new CountriesModelItem;
    itemTV->name = QObject::trUtf8("Tuvalu");
    itemTV->isoCode = "TV";
    countries.append(itemTV);
    CountriesModelItem *itemUG = new CountriesModelItem;
    itemUG->name = QObject::trUtf8("Uganda");
    itemUG->isoCode = "UG";
    countries.append(itemUG);
    CountriesModelItem *itemUA = new CountriesModelItem;
    itemUA->name = QObject::trUtf8("Ukraine");
    itemUA->isoCode = "UA";
    countries.append(itemUA);
    CountriesModelItem *itemAE = new CountriesModelItem;
    itemAE->name = QObject::trUtf8("United Arab Emirates");
    itemAE->isoCode = "AE";
    countries.append(itemAE);
    CountriesModelItem *itemGB = new CountriesModelItem;
    itemGB->name = QObject::trUtf8("United Kingdom");
    itemGB->isoCode = "GB";
    countries.append(itemGB);
    CountriesModelItem *itemUS = new CountriesModelItem;
    itemUS->name = QObject::trUtf8("United States");
    itemUS->isoCode = "US";
    countries.append(itemUS);
    CountriesModelItem *itemUM = new CountriesModelItem;
    itemUM->name = QObject::trUtf8("United States Minor Outlying Islands");
    itemUM->isoCode = "UM";
    countries.append(itemUM);
    CountriesModelItem *itemUY = new CountriesModelItem;
    itemUY->name = QObject::trUtf8("Uruguay");
    itemUY->isoCode = "UY";
    countries.append(itemUY);
    CountriesModelItem *itemUZ = new CountriesModelItem;
    itemUZ->name = QObject::trUtf8("Uzbekistan");
    itemUZ->isoCode = "UZ";
    countries.append(itemUZ);
    CountriesModelItem *itemVU = new CountriesModelItem;
    itemVU->name = QObject::trUtf8("Vanuatu");
    itemVU->isoCode = "VU";
    countries.append(itemVU);
    CountriesModelItem *itemVE = new CountriesModelItem;
    itemVE->name = QObject::trUtf8("Venezuela");
    itemVE->isoCode = "VE";
    countries.append(itemVE);
    CountriesModelItem *itemVN = new CountriesModelItem;
    itemVN->name = QObject::trUtf8("Viet Nam");
    itemVN->isoCode = "VN";
    countries.append(itemVN);
    CountriesModelItem *itemVG = new CountriesModelItem;
    itemVG->name = QObject::trUtf8("Virgin Islands, British");
    itemVG->isoCode = "VG";
    countries.append(itemVG);
    CountriesModelItem *itemVI = new CountriesModelItem;
    itemVI->name = QObject::trUtf8("Virgin Islands, U.S.");
    itemVI->isoCode = "VI";
    countries.append(itemVI);
    CountriesModelItem *itemWF = new CountriesModelItem;
    itemWF->name = QObject::trUtf8("Wallis and Futuna");
    itemWF->isoCode = "WF";
    countries.append(itemWF);
    CountriesModelItem *itemEH = new CountriesModelItem;
    itemEH->name = QObject::trUtf8("Western Sahara");
    itemEH->isoCode = "EH";
    countries.append(itemEH);
    CountriesModelItem *itemYE = new CountriesModelItem;
    itemYE->name = QObject::trUtf8("Yemen");
    itemYE->isoCode = "YE";
    countries.append(itemYE);
    CountriesModelItem *itemZM = new CountriesModelItem;
    itemZM->name = QObject::trUtf8("Zambia");
    itemZM->isoCode = "ZM";
    countries.append(itemZM);
    CountriesModelItem *itemZW = new CountriesModelItem;
    itemZW->name = QObject::trUtf8("Zimbabwe");
    itemZW->isoCode = "ZW";
    countries.append(itemZW);


    data = countries;
    data.prepend(all);
}

QString CountriesModelPrivate::unaccent(const QString &string)
{
    QString canonicalForm = string.toLower().normalized(QString::NormalizationForm_D);
    QString returnedString;
    foreach (QChar c, canonicalForm) {
        if (c.category() != QChar::Mark_NonSpacing &&
            c.category() != QChar::Mark_SpacingCombining) {
              returnedString.append(c);
         }
    }

    return returnedString;
}

////// End of private class //////

CountriesModel::CountriesModel(QObject *parent):
    QAbstractListModel(parent),
    d_ptr(new CountriesModelPrivate)
{
    // Definition of roles
    QHash <int, QByteArray> roles;
    roles.insert(NameRole, "name");
    roles.insert(IsoCodeRole, "isoCode");
    setRoleNames(roles);
}

CountriesModel::~CountriesModel()
{
    Q_D(CountriesModel);
    delete d->all;
    while (!d->countries.isEmpty()) {
        delete d->countries.takeFirst();
    }
}

QString CountriesModel::currentCountry() const
{
    Q_D(const CountriesModel);
    return d->current->name;
}

QString CountriesModel::currentIsoCode() const
{
    Q_D(const CountriesModel);
    return d->current->isoCode;
}

QString CountriesModel::filter() const
{
    Q_D(const CountriesModel);
    return d->filter;
}

int  CountriesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const CountriesModel);
    return d->data.count();
}

int CountriesModel::count() const
{
    return rowCount();
}

QVariant CountriesModel::data(const QModelIndex &index, int role) const
{
    Q_D(const CountriesModel);
    if (index.row() < 0 or index.row() >= rowCount()) {
        return QVariant();
    }
    CountriesModelItem *item = d->data.at(index.row());

    switch(role) {
    case NameRole:
        return item->name;
        break;
    case IsoCodeRole:
        return item->isoCode;
        break;
    default:
        return QVariant();
        break;
    }
}

void CountriesModel::setFilter(const QString &filter)
{
    Q_D(CountriesModel);
    if (d->filter != filter) {
        d->filter = filter;
        emit filterChanged();

        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        d->data.clear();
        endRemoveRows();

        if (filter.isEmpty()) {
            d->data = d->countries;
            d->data.prepend(d->all);
        } else {
            foreach (CountriesModelItem *item, d->countries) {
                if (d->unaccent(item->name).startsWith(d->unaccent(filter))) {
                    d->data.append(item);
                }
            }
        }

        beginInsertRows(QModelIndex(), 0, d->data.count() - 1);
        emit countChanged();
        endInsertRows();
    }
}

void CountriesModel::select(int index)
{
    Q_D(CountriesModel);
    if (index < 0 || index >= rowCount()) {
        return;
    }

    CountriesModelItem *newItem = d->data.at(index);
    if (d->current != newItem) {
        d->current = newItem;
        emit currentCountryChanged();
        emit currentIsoCodeChanged();
    }
}

}

}
