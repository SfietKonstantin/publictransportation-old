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
    itemAF->name = QObject::tr("Afghanistan");
    itemAF->isoCode = "AF";
    countries.append(itemAF);
    CountriesModelItem *itemAX = new CountriesModelItem;
    itemAX->name = QObject::tr("Åland Islands");
    itemAX->isoCode = "AX";
    countries.append(itemAX);
    CountriesModelItem *itemAL = new CountriesModelItem;
    itemAL->name = QObject::tr("Albania");
    itemAL->isoCode = "AL";
    countries.append(itemAL);
    CountriesModelItem *itemDZ = new CountriesModelItem;
    itemDZ->name = QObject::tr("Algeria");
    itemDZ->isoCode = "DZ";
    countries.append(itemDZ);
    CountriesModelItem *itemAS = new CountriesModelItem;
    itemAS->name = QObject::tr("American Samoa");
    itemAS->isoCode = "AS";
    countries.append(itemAS);
    CountriesModelItem *itemAD = new CountriesModelItem;
    itemAD->name = QObject::tr("Andorra");
    itemAD->isoCode = "AD";
    countries.append(itemAD);
    CountriesModelItem *itemAO = new CountriesModelItem;
    itemAO->name = QObject::tr("Angola");
    itemAO->isoCode = "AO";
    countries.append(itemAO);
    CountriesModelItem *itemAI = new CountriesModelItem;
    itemAI->name = QObject::tr("Anguilla");
    itemAI->isoCode = "AI";
    countries.append(itemAI);
    CountriesModelItem *itemAQ = new CountriesModelItem;
    itemAQ->name = QObject::tr("Antarctica");
    itemAQ->isoCode = "AQ";
    countries.append(itemAQ);
    CountriesModelItem *itemAG = new CountriesModelItem;
    itemAG->name = QObject::tr("Antigua and Barbuda");
    itemAG->isoCode = "AG";
    countries.append(itemAG);
    CountriesModelItem *itemAR = new CountriesModelItem;
    itemAR->name = QObject::tr("Argentina");
    itemAR->isoCode = "AR";
    countries.append(itemAR);
    CountriesModelItem *itemAM = new CountriesModelItem;
    itemAM->name = QObject::tr("Armenia");
    itemAM->isoCode = "AM";
    countries.append(itemAM);
    CountriesModelItem *itemAW = new CountriesModelItem;
    itemAW->name = QObject::tr("Aruba");
    itemAW->isoCode = "AW";
    countries.append(itemAW);
    CountriesModelItem *itemAU = new CountriesModelItem;
    itemAU->name = QObject::tr("Australia");
    itemAU->isoCode = "AU";
    countries.append(itemAU);
    CountriesModelItem *itemAT = new CountriesModelItem;
    itemAT->name = QObject::tr("Austria");
    itemAT->isoCode = "AT";
    countries.append(itemAT);
    CountriesModelItem *itemAZ = new CountriesModelItem;
    itemAZ->name = QObject::tr("Azerbaijan");
    itemAZ->isoCode = "AZ";
    countries.append(itemAZ);
    CountriesModelItem *itemBS = new CountriesModelItem;
    itemBS->name = QObject::tr("Bahamas");
    itemBS->isoCode = "BS";
    countries.append(itemBS);
    CountriesModelItem *itemBH = new CountriesModelItem;
    itemBH->name = QObject::tr("Bahrain");
    itemBH->isoCode = "BH";
    countries.append(itemBH);
    CountriesModelItem *itemBD = new CountriesModelItem;
    itemBD->name = QObject::tr("Bangladesh");
    itemBD->isoCode = "BD";
    countries.append(itemBD);
    CountriesModelItem *itemBB = new CountriesModelItem;
    itemBB->name = QObject::tr("Barbados");
    itemBB->isoCode = "BB";
    countries.append(itemBB);
    CountriesModelItem *itemBY = new CountriesModelItem;
    itemBY->name = QObject::tr("Belarus");
    itemBY->isoCode = "BY";
    countries.append(itemBY);
    CountriesModelItem *itemBE = new CountriesModelItem;
    itemBE->name = QObject::tr("Belgium");
    itemBE->isoCode = "BE";
    countries.append(itemBE);
    CountriesModelItem *itemBZ = new CountriesModelItem;
    itemBZ->name = QObject::tr("Belize");
    itemBZ->isoCode = "BZ";
    countries.append(itemBZ);
    CountriesModelItem *itemBJ = new CountriesModelItem;
    itemBJ->name = QObject::tr("Benin");
    itemBJ->isoCode = "BJ";
    countries.append(itemBJ);
    CountriesModelItem *itemBM = new CountriesModelItem;
    itemBM->name = QObject::tr("Bermuda");
    itemBM->isoCode = "BM";
    countries.append(itemBM);
    CountriesModelItem *itemBT = new CountriesModelItem;
    itemBT->name = QObject::tr("Bhutan");
    itemBT->isoCode = "BT";
    countries.append(itemBT);
    CountriesModelItem *itemBO = new CountriesModelItem;
    itemBO->name = QObject::tr("Bolivia");
    itemBO->isoCode = "BO";
    countries.append(itemBO);
    CountriesModelItem *itemBA = new CountriesModelItem;
    itemBA->name = QObject::tr("Bosnia and Herzegovina");
    itemBA->isoCode = "BA";
    countries.append(itemBA);
    CountriesModelItem *itemBW = new CountriesModelItem;
    itemBW->name = QObject::tr("Botswana");
    itemBW->isoCode = "BW";
    countries.append(itemBW);
    CountriesModelItem *itemBV = new CountriesModelItem;
    itemBV->name = QObject::tr("Bouvet Island");
    itemBV->isoCode = "BV";
    countries.append(itemBV);
    CountriesModelItem *itemBR = new CountriesModelItem;
    itemBR->name = QObject::tr("Brazil");
    itemBR->isoCode = "BR";
    countries.append(itemBR);
    CountriesModelItem *itemIO = new CountriesModelItem;
    itemIO->name = QObject::tr("British Indian Ocean Territory");
    itemIO->isoCode = "IO";
    countries.append(itemIO);
    CountriesModelItem *itemBN = new CountriesModelItem;
    itemBN->name = QObject::tr("Brunei Darussalam");
    itemBN->isoCode = "BN";
    countries.append(itemBN);
    CountriesModelItem *itemBG = new CountriesModelItem;
    itemBG->name = QObject::tr("Bulgaria");
    itemBG->isoCode = "BG";
    countries.append(itemBG);
    CountriesModelItem *itemBF = new CountriesModelItem;
    itemBF->name = QObject::tr("Burkina Faso");
    itemBF->isoCode = "BF";
    countries.append(itemBF);
    CountriesModelItem *itemBI = new CountriesModelItem;
    itemBI->name = QObject::tr("Burundi");
    itemBI->isoCode = "BI";
    countries.append(itemBI);
    CountriesModelItem *itemKH = new CountriesModelItem;
    itemKH->name = QObject::tr("Cambodia");
    itemKH->isoCode = "KH";
    countries.append(itemKH);
    CountriesModelItem *itemCM = new CountriesModelItem;
    itemCM->name = QObject::tr("Cameroon");
    itemCM->isoCode = "CM";
    countries.append(itemCM);
    CountriesModelItem *itemCA = new CountriesModelItem;
    itemCA->name = QObject::tr("Canada");
    itemCA->isoCode = "CA";
    countries.append(itemCA);
    CountriesModelItem *itemCV = new CountriesModelItem;
    itemCV->name = QObject::tr("Cape Verde");
    itemCV->isoCode = "CV";
    countries.append(itemCV);
    CountriesModelItem *itemKY = new CountriesModelItem;
    itemKY->name = QObject::tr("Cayman Islands");
    itemKY->isoCode = "KY";
    countries.append(itemKY);
    CountriesModelItem *itemCF = new CountriesModelItem;
    itemCF->name = QObject::tr("Central African Republic");
    itemCF->isoCode = "CF";
    countries.append(itemCF);
    CountriesModelItem *itemTD = new CountriesModelItem;
    itemTD->name = QObject::tr("Chad");
    itemTD->isoCode = "TD";
    countries.append(itemTD);
    CountriesModelItem *itemCL = new CountriesModelItem;
    itemCL->name = QObject::tr("Chile");
    itemCL->isoCode = "CL";
    countries.append(itemCL);
    CountriesModelItem *itemCN = new CountriesModelItem;
    itemCN->name = QObject::tr("China");
    itemCN->isoCode = "CN";
    countries.append(itemCN);
    CountriesModelItem *itemCX = new CountriesModelItem;
    itemCX->name = QObject::tr("Christmas Island");
    itemCX->isoCode = "CX";
    countries.append(itemCX);
    CountriesModelItem *itemCC = new CountriesModelItem;
    itemCC->name = QObject::tr("Cocos (Keeling) Islands");
    itemCC->isoCode = "CC";
    countries.append(itemCC);
    CountriesModelItem *itemCO = new CountriesModelItem;
    itemCO->name = QObject::tr("Colombia");
    itemCO->isoCode = "CO";
    countries.append(itemCO);
    CountriesModelItem *itemKM = new CountriesModelItem;
    itemKM->name = QObject::tr("Comoros");
    itemKM->isoCode = "KM";
    countries.append(itemKM);
    CountriesModelItem *itemCG = new CountriesModelItem;
    itemCG->name = QObject::tr("Congo");
    itemCG->isoCode = "CG";
    countries.append(itemCG);
    CountriesModelItem *itemCD = new CountriesModelItem;
    itemCD->name = QObject::tr("Congo, The Democratic Republic of The");
    itemCD->isoCode = "CD";
    countries.append(itemCD);
    CountriesModelItem *itemCK = new CountriesModelItem;
    itemCK->name = QObject::tr("Cook Islands");
    itemCK->isoCode = "CK";
    countries.append(itemCK);
    CountriesModelItem *itemCR = new CountriesModelItem;
    itemCR->name = QObject::tr("Costa Rica");
    itemCR->isoCode = "CR";
    countries.append(itemCR);
    CountriesModelItem *itemCI = new CountriesModelItem;
    itemCI->name = QObject::tr("Cote D'ivoire");
    itemCI->isoCode = "CI";
    countries.append(itemCI);
    CountriesModelItem *itemHR = new CountriesModelItem;
    itemHR->name = QObject::tr("Croatia");
    itemHR->isoCode = "HR";
    countries.append(itemHR);
    CountriesModelItem *itemCU = new CountriesModelItem;
    itemCU->name = QObject::tr("Cuba");
    itemCU->isoCode = "CU";
    countries.append(itemCU);
    CountriesModelItem *itemCY = new CountriesModelItem;
    itemCY->name = QObject::tr("Cyprus");
    itemCY->isoCode = "CY";
    countries.append(itemCY);
    CountriesModelItem *itemCZ = new CountriesModelItem;
    itemCZ->name = QObject::tr("Czech Republic");
    itemCZ->isoCode = "CZ";
    countries.append(itemCZ);
    CountriesModelItem *itemDK = new CountriesModelItem;
    itemDK->name = QObject::tr("Denmark");
    itemDK->isoCode = "DK";
    countries.append(itemDK);
    CountriesModelItem *itemDJ = new CountriesModelItem;
    itemDJ->name = QObject::tr("Djibouti");
    itemDJ->isoCode = "DJ";
    countries.append(itemDJ);
    CountriesModelItem *itemDM = new CountriesModelItem;
    itemDM->name = QObject::tr("Dominica");
    itemDM->isoCode = "DM";
    countries.append(itemDM);
    CountriesModelItem *itemDO = new CountriesModelItem;
    itemDO->name = QObject::tr("Dominican Republic");
    itemDO->isoCode = "DO";
    countries.append(itemDO);
    CountriesModelItem *itemEC = new CountriesModelItem;
    itemEC->name = QObject::tr("Ecuador");
    itemEC->isoCode = "EC";
    countries.append(itemEC);
    CountriesModelItem *itemEG = new CountriesModelItem;
    itemEG->name = QObject::tr("Egypt");
    itemEG->isoCode = "EG";
    countries.append(itemEG);
    CountriesModelItem *itemSV = new CountriesModelItem;
    itemSV->name = QObject::tr("El Salvador");
    itemSV->isoCode = "SV";
    countries.append(itemSV);
    CountriesModelItem *itemGQ = new CountriesModelItem;
    itemGQ->name = QObject::tr("Equatorial Guinea");
    itemGQ->isoCode = "GQ";
    countries.append(itemGQ);
    CountriesModelItem *itemER = new CountriesModelItem;
    itemER->name = QObject::tr("Eritrea");
    itemER->isoCode = "ER";
    countries.append(itemER);
    CountriesModelItem *itemEE = new CountriesModelItem;
    itemEE->name = QObject::tr("Estonia");
    itemEE->isoCode = "EE";
    countries.append(itemEE);
    CountriesModelItem *itemET = new CountriesModelItem;
    itemET->name = QObject::tr("Ethiopia");
    itemET->isoCode = "ET";
    countries.append(itemET);
    CountriesModelItem *itemFK = new CountriesModelItem;
    itemFK->name = QObject::tr("Falkland Islands (Malvinas)");
    itemFK->isoCode = "FK";
    countries.append(itemFK);
    CountriesModelItem *itemFO = new CountriesModelItem;
    itemFO->name = QObject::tr("Faroe Islands");
    itemFO->isoCode = "FO";
    countries.append(itemFO);
    CountriesModelItem *itemFJ = new CountriesModelItem;
    itemFJ->name = QObject::tr("Fiji");
    itemFJ->isoCode = "FJ";
    countries.append(itemFJ);
    CountriesModelItem *itemFI = new CountriesModelItem;
    itemFI->name = QObject::tr("Finland");
    itemFI->isoCode = "FI";
    countries.append(itemFI);
    CountriesModelItem *itemFR = new CountriesModelItem;
    itemFR->name = QObject::tr("France");
    itemFR->isoCode = "FR";
    countries.append(itemFR);
    CountriesModelItem *itemGF = new CountriesModelItem;
    itemGF->name = QObject::tr("French Guiana");
    itemGF->isoCode = "GF";
    countries.append(itemGF);
    CountriesModelItem *itemPF = new CountriesModelItem;
    itemPF->name = QObject::tr("French Polynesia");
    itemPF->isoCode = "PF";
    countries.append(itemPF);
    CountriesModelItem *itemTF = new CountriesModelItem;
    itemTF->name = QObject::tr("French Southern Territories");
    itemTF->isoCode = "TF";
    countries.append(itemTF);
    CountriesModelItem *itemGA = new CountriesModelItem;
    itemGA->name = QObject::tr("Gabon");
    itemGA->isoCode = "GA";
    countries.append(itemGA);
    CountriesModelItem *itemGM = new CountriesModelItem;
    itemGM->name = QObject::tr("Gambia");
    itemGM->isoCode = "GM";
    countries.append(itemGM);
    CountriesModelItem *itemGE = new CountriesModelItem;
    itemGE->name = QObject::tr("Georgia");
    itemGE->isoCode = "GE";
    countries.append(itemGE);
    CountriesModelItem *itemDE = new CountriesModelItem;
    itemDE->name = QObject::tr("Germany");
    itemDE->isoCode = "DE";
    countries.append(itemDE);
    CountriesModelItem *itemGH = new CountriesModelItem;
    itemGH->name = QObject::tr("Ghana");
    itemGH->isoCode = "GH";
    countries.append(itemGH);
    CountriesModelItem *itemGI = new CountriesModelItem;
    itemGI->name = QObject::tr("Gibraltar");
    itemGI->isoCode = "GI";
    countries.append(itemGI);
    CountriesModelItem *itemGR = new CountriesModelItem;
    itemGR->name = QObject::tr("Greece");
    itemGR->isoCode = "GR";
    countries.append(itemGR);
    CountriesModelItem *itemGL = new CountriesModelItem;
    itemGL->name = QObject::tr("Greenland");
    itemGL->isoCode = "GL";
    countries.append(itemGL);
    CountriesModelItem *itemGD = new CountriesModelItem;
    itemGD->name = QObject::tr("Grenada");
    itemGD->isoCode = "GD";
    countries.append(itemGD);
    CountriesModelItem *itemGP = new CountriesModelItem;
    itemGP->name = QObject::tr("Guadeloupe");
    itemGP->isoCode = "GP";
    countries.append(itemGP);
    CountriesModelItem *itemGU = new CountriesModelItem;
    itemGU->name = QObject::tr("Guam");
    itemGU->isoCode = "GU";
    countries.append(itemGU);
    CountriesModelItem *itemGT = new CountriesModelItem;
    itemGT->name = QObject::tr("Guatemala");
    itemGT->isoCode = "GT";
    countries.append(itemGT);
    CountriesModelItem *itemGG = new CountriesModelItem;
    itemGG->name = QObject::tr("Guernsey");
    itemGG->isoCode = "GG";
    countries.append(itemGG);
    CountriesModelItem *itemGN = new CountriesModelItem;
    itemGN->name = QObject::tr("Guinea");
    itemGN->isoCode = "GN";
    countries.append(itemGN);
    CountriesModelItem *itemGW = new CountriesModelItem;
    itemGW->name = QObject::tr("Guinea-bissau");
    itemGW->isoCode = "GW";
    countries.append(itemGW);
    CountriesModelItem *itemGY = new CountriesModelItem;
    itemGY->name = QObject::tr("Guyana");
    itemGY->isoCode = "GY";
    countries.append(itemGY);
    CountriesModelItem *itemHT = new CountriesModelItem;
    itemHT->name = QObject::tr("Haiti");
    itemHT->isoCode = "HT";
    countries.append(itemHT);
    CountriesModelItem *itemHM = new CountriesModelItem;
    itemHM->name = QObject::tr("Heard Island and Mcdonald Islands");
    itemHM->isoCode = "HM";
    countries.append(itemHM);
    CountriesModelItem *itemVA = new CountriesModelItem;
    itemVA->name = QObject::tr("Holy See (Vatican City State)");
    itemVA->isoCode = "VA";
    countries.append(itemVA);
    CountriesModelItem *itemHN = new CountriesModelItem;
    itemHN->name = QObject::tr("Honduras");
    itemHN->isoCode = "HN";
    countries.append(itemHN);
    CountriesModelItem *itemHK = new CountriesModelItem;
    itemHK->name = QObject::tr("Hong Kong");
    itemHK->isoCode = "HK";
    countries.append(itemHK);
    CountriesModelItem *itemHU = new CountriesModelItem;
    itemHU->name = QObject::tr("Hungary");
    itemHU->isoCode = "HU";
    countries.append(itemHU);
    CountriesModelItem *itemIS = new CountriesModelItem;
    itemIS->name = QObject::tr("Iceland");
    itemIS->isoCode = "IS";
    countries.append(itemIS);
    CountriesModelItem *itemIN = new CountriesModelItem;
    itemIN->name = QObject::tr("India");
    itemIN->isoCode = "IN";
    countries.append(itemIN);
    CountriesModelItem *itemID = new CountriesModelItem;
    itemID->name = QObject::tr("Indonesia");
    itemID->isoCode = "ID";
    countries.append(itemID);
    CountriesModelItem *itemIR = new CountriesModelItem;
    itemIR->name = QObject::tr("Iran, Islamic Republic of");
    itemIR->isoCode = "IR";
    countries.append(itemIR);
    CountriesModelItem *itemIQ = new CountriesModelItem;
    itemIQ->name = QObject::tr("Iraq");
    itemIQ->isoCode = "IQ";
    countries.append(itemIQ);
    CountriesModelItem *itemIE = new CountriesModelItem;
    itemIE->name = QObject::tr("Ireland");
    itemIE->isoCode = "IE";
    countries.append(itemIE);
    CountriesModelItem *itemIM = new CountriesModelItem;
    itemIM->name = QObject::tr("Isle of Man");
    itemIM->isoCode = "IM";
    countries.append(itemIM);
    CountriesModelItem *itemIL = new CountriesModelItem;
    itemIL->name = QObject::tr("Israel");
    itemIL->isoCode = "IL";
    countries.append(itemIL);
    CountriesModelItem *itemIT = new CountriesModelItem;
    itemIT->name = QObject::tr("Italy");
    itemIT->isoCode = "IT";
    countries.append(itemIT);
    CountriesModelItem *itemJM = new CountriesModelItem;
    itemJM->name = QObject::tr("Jamaica");
    itemJM->isoCode = "JM";
    countries.append(itemJM);
    CountriesModelItem *itemJP = new CountriesModelItem;
    itemJP->name = QObject::tr("Japan");
    itemJP->isoCode = "JP";
    countries.append(itemJP);
    CountriesModelItem *itemJE = new CountriesModelItem;
    itemJE->name = QObject::tr("Jersey");
    itemJE->isoCode = "JE";
    countries.append(itemJE);
    CountriesModelItem *itemJO = new CountriesModelItem;
    itemJO->name = QObject::tr("Jordan");
    itemJO->isoCode = "JO";
    countries.append(itemJO);
    CountriesModelItem *itemKZ = new CountriesModelItem;
    itemKZ->name = QObject::tr("Kazakhstan");
    itemKZ->isoCode = "KZ";
    countries.append(itemKZ);
    CountriesModelItem *itemKE = new CountriesModelItem;
    itemKE->name = QObject::tr("Kenya");
    itemKE->isoCode = "KE";
    countries.append(itemKE);
    CountriesModelItem *itemKI = new CountriesModelItem;
    itemKI->name = QObject::tr("Kiribati");
    itemKI->isoCode = "KI";
    countries.append(itemKI);
    CountriesModelItem *itemKP = new CountriesModelItem;
    itemKP->name = QObject::tr("Korea, Democratic People's Republic of");
    itemKP->isoCode = "KP";
    countries.append(itemKP);
    CountriesModelItem *itemKR = new CountriesModelItem;
    itemKR->name = QObject::tr("Korea, Republic of");
    itemKR->isoCode = "KR";
    countries.append(itemKR);
    CountriesModelItem *itemKW = new CountriesModelItem;
    itemKW->name = QObject::tr("Kuwait");
    itemKW->isoCode = "KW";
    countries.append(itemKW);
    CountriesModelItem *itemKG = new CountriesModelItem;
    itemKG->name = QObject::tr("Kyrgyzstan");
    itemKG->isoCode = "KG";
    countries.append(itemKG);
    CountriesModelItem *itemLA = new CountriesModelItem;
    itemLA->name = QObject::tr("Lao People's Democratic Republic");
    itemLA->isoCode = "LA";
    countries.append(itemLA);
    CountriesModelItem *itemLV = new CountriesModelItem;
    itemLV->name = QObject::tr("Latvia");
    itemLV->isoCode = "LV";
    countries.append(itemLV);
    CountriesModelItem *itemLB = new CountriesModelItem;
    itemLB->name = QObject::tr("Lebanon");
    itemLB->isoCode = "LB";
    countries.append(itemLB);
    CountriesModelItem *itemLS = new CountriesModelItem;
    itemLS->name = QObject::tr("Lesotho");
    itemLS->isoCode = "LS";
    countries.append(itemLS);
    CountriesModelItem *itemLR = new CountriesModelItem;
    itemLR->name = QObject::tr("Liberia");
    itemLR->isoCode = "LR";
    countries.append(itemLR);
    CountriesModelItem *itemLY = new CountriesModelItem;
    itemLY->name = QObject::tr("Libyan Arab Jamahiriya");
    itemLY->isoCode = "LY";
    countries.append(itemLY);
    CountriesModelItem *itemLI = new CountriesModelItem;
    itemLI->name = QObject::tr("Liechtenstein");
    itemLI->isoCode = "LI";
    countries.append(itemLI);
    CountriesModelItem *itemLT = new CountriesModelItem;
    itemLT->name = QObject::tr("Lithuania");
    itemLT->isoCode = "LT";
    countries.append(itemLT);
    CountriesModelItem *itemLU = new CountriesModelItem;
    itemLU->name = QObject::tr("Luxembourg");
    itemLU->isoCode = "LU";
    countries.append(itemLU);
    CountriesModelItem *itemMO = new CountriesModelItem;
    itemMO->name = QObject::tr("Macao");
    itemMO->isoCode = "MO";
    countries.append(itemMO);
    CountriesModelItem *itemMK = new CountriesModelItem;
    itemMK->name = QObject::tr("Macedonia, The Former Yugoslav Republic of");
    itemMK->isoCode = "MK";
    countries.append(itemMK);
    CountriesModelItem *itemMG = new CountriesModelItem;
    itemMG->name = QObject::tr("Madagascar");
    itemMG->isoCode = "MG";
    countries.append(itemMG);
    CountriesModelItem *itemMW = new CountriesModelItem;
    itemMW->name = QObject::tr("Malawi");
    itemMW->isoCode = "MW";
    countries.append(itemMW);
    CountriesModelItem *itemMY = new CountriesModelItem;
    itemMY->name = QObject::tr("Malaysia");
    itemMY->isoCode = "MY";
    countries.append(itemMY);
    CountriesModelItem *itemMV = new CountriesModelItem;
    itemMV->name = QObject::tr("Maldives");
    itemMV->isoCode = "MV";
    countries.append(itemMV);
    CountriesModelItem *itemML = new CountriesModelItem;
    itemML->name = QObject::tr("Mali");
    itemML->isoCode = "ML";
    countries.append(itemML);
    CountriesModelItem *itemMT = new CountriesModelItem;
    itemMT->name = QObject::tr("Malta");
    itemMT->isoCode = "MT";
    countries.append(itemMT);
    CountriesModelItem *itemMH = new CountriesModelItem;
    itemMH->name = QObject::tr("Marshall Islands");
    itemMH->isoCode = "MH";
    countries.append(itemMH);
    CountriesModelItem *itemMQ = new CountriesModelItem;
    itemMQ->name = QObject::tr("Martinique");
    itemMQ->isoCode = "MQ";
    countries.append(itemMQ);
    CountriesModelItem *itemMR = new CountriesModelItem;
    itemMR->name = QObject::tr("Mauritania");
    itemMR->isoCode = "MR";
    countries.append(itemMR);
    CountriesModelItem *itemMU = new CountriesModelItem;
    itemMU->name = QObject::tr("Mauritius");
    itemMU->isoCode = "MU";
    countries.append(itemMU);
    CountriesModelItem *itemYT = new CountriesModelItem;
    itemYT->name = QObject::tr("Mayotte");
    itemYT->isoCode = "YT";
    countries.append(itemYT);
    CountriesModelItem *itemMX = new CountriesModelItem;
    itemMX->name = QObject::tr("Mexico");
    itemMX->isoCode = "MX";
    countries.append(itemMX);
    CountriesModelItem *itemFM = new CountriesModelItem;
    itemFM->name = QObject::tr("Micronesia, Federated States of");
    itemFM->isoCode = "FM";
    countries.append(itemFM);
    CountriesModelItem *itemMD = new CountriesModelItem;
    itemMD->name = QObject::tr("Moldova, Republic of");
    itemMD->isoCode = "MD";
    countries.append(itemMD);
    CountriesModelItem *itemMC = new CountriesModelItem;
    itemMC->name = QObject::tr("Monaco");
    itemMC->isoCode = "MC";
    countries.append(itemMC);
    CountriesModelItem *itemMN = new CountriesModelItem;
    itemMN->name = QObject::tr("Mongolia");
    itemMN->isoCode = "MN";
    countries.append(itemMN);
    CountriesModelItem *itemME = new CountriesModelItem;
    itemME->name = QObject::tr("Montenegro");
    itemME->isoCode = "ME";
    countries.append(itemME);
    CountriesModelItem *itemMS = new CountriesModelItem;
    itemMS->name = QObject::tr("Montserrat");
    itemMS->isoCode = "MS";
    countries.append(itemMS);
    CountriesModelItem *itemMA = new CountriesModelItem;
    itemMA->name = QObject::tr("Morocco");
    itemMA->isoCode = "MA";
    countries.append(itemMA);
    CountriesModelItem *itemMZ = new CountriesModelItem;
    itemMZ->name = QObject::tr("Mozambique");
    itemMZ->isoCode = "MZ";
    countries.append(itemMZ);
    CountriesModelItem *itemMM = new CountriesModelItem;
    itemMM->name = QObject::tr("Myanmar");
    itemMM->isoCode = "MM";
    countries.append(itemMM);
    CountriesModelItem *itemNA = new CountriesModelItem;
    itemNA->name = QObject::tr("Namibia");
    itemNA->isoCode = "NA";
    countries.append(itemNA);
    CountriesModelItem *itemNR = new CountriesModelItem;
    itemNR->name = QObject::tr("Nauru");
    itemNR->isoCode = "NR";
    countries.append(itemNR);
    CountriesModelItem *itemNP = new CountriesModelItem;
    itemNP->name = QObject::tr("Nepal");
    itemNP->isoCode = "NP";
    countries.append(itemNP);
    CountriesModelItem *itemNL = new CountriesModelItem;
    itemNL->name = QObject::tr("Netherlands");
    itemNL->isoCode = "NL";
    countries.append(itemNL);
    CountriesModelItem *itemAN = new CountriesModelItem;
    itemAN->name = QObject::tr("Netherlands Antilles");
    itemAN->isoCode = "AN";
    countries.append(itemAN);
    CountriesModelItem *itemNC = new CountriesModelItem;
    itemNC->name = QObject::tr("New Caledonia");
    itemNC->isoCode = "NC";
    countries.append(itemNC);
    CountriesModelItem *itemNZ = new CountriesModelItem;
    itemNZ->name = QObject::tr("New Zealand");
    itemNZ->isoCode = "NZ";
    countries.append(itemNZ);
    CountriesModelItem *itemNI = new CountriesModelItem;
    itemNI->name = QObject::tr("Nicaragua");
    itemNI->isoCode = "NI";
    countries.append(itemNI);
    CountriesModelItem *itemNE = new CountriesModelItem;
    itemNE->name = QObject::tr("Niger");
    itemNE->isoCode = "NE";
    countries.append(itemNE);
    CountriesModelItem *itemNG = new CountriesModelItem;
    itemNG->name = QObject::tr("Nigeria");
    itemNG->isoCode = "NG";
    countries.append(itemNG);
    CountriesModelItem *itemNU = new CountriesModelItem;
    itemNU->name = QObject::tr("Niue");
    itemNU->isoCode = "NU";
    countries.append(itemNU);
    CountriesModelItem *itemNF = new CountriesModelItem;
    itemNF->name = QObject::tr("Norfolk Island");
    itemNF->isoCode = "NF";
    countries.append(itemNF);
    CountriesModelItem *itemMP = new CountriesModelItem;
    itemMP->name = QObject::tr("Northern Mariana Islands");
    itemMP->isoCode = "MP";
    countries.append(itemMP);
    CountriesModelItem *itemNO = new CountriesModelItem;
    itemNO->name = QObject::tr("Norway");
    itemNO->isoCode = "NO";
    countries.append(itemNO);
    CountriesModelItem *itemOM = new CountriesModelItem;
    itemOM->name = QObject::tr("Oman");
    itemOM->isoCode = "OM";
    countries.append(itemOM);
    CountriesModelItem *itemPK = new CountriesModelItem;
    itemPK->name = QObject::tr("Pakistan");
    itemPK->isoCode = "PK";
    countries.append(itemPK);
    CountriesModelItem *itemPW = new CountriesModelItem;
    itemPW->name = QObject::tr("Palau");
    itemPW->isoCode = "PW";
    countries.append(itemPW);
    CountriesModelItem *itemPS = new CountriesModelItem;
    itemPS->name = QObject::tr("Palestinian Territory, Occupied");
    itemPS->isoCode = "PS";
    countries.append(itemPS);
    CountriesModelItem *itemPA = new CountriesModelItem;
    itemPA->name = QObject::tr("Panama");
    itemPA->isoCode = "PA";
    countries.append(itemPA);
    CountriesModelItem *itemPG = new CountriesModelItem;
    itemPG->name = QObject::tr("Papua New Guinea");
    itemPG->isoCode = "PG";
    countries.append(itemPG);
    CountriesModelItem *itemPY = new CountriesModelItem;
    itemPY->name = QObject::tr("Paraguay");
    itemPY->isoCode = "PY";
    countries.append(itemPY);
    CountriesModelItem *itemPE = new CountriesModelItem;
    itemPE->name = QObject::tr("Peru");
    itemPE->isoCode = "PE";
    countries.append(itemPE);
    CountriesModelItem *itemPH = new CountriesModelItem;
    itemPH->name = QObject::tr("Philippines");
    itemPH->isoCode = "PH";
    countries.append(itemPH);
    CountriesModelItem *itemPN = new CountriesModelItem;
    itemPN->name = QObject::tr("Pitcairn");
    itemPN->isoCode = "PN";
    countries.append(itemPN);
    CountriesModelItem *itemPL = new CountriesModelItem;
    itemPL->name = QObject::tr("Poland");
    itemPL->isoCode = "PL";
    countries.append(itemPL);
    CountriesModelItem *itemPT = new CountriesModelItem;
    itemPT->name = QObject::tr("Portugal");
    itemPT->isoCode = "PT";
    countries.append(itemPT);
    CountriesModelItem *itemPR = new CountriesModelItem;
    itemPR->name = QObject::tr("Puerto Rico");
    itemPR->isoCode = "PR";
    countries.append(itemPR);
    CountriesModelItem *itemQA = new CountriesModelItem;
    itemQA->name = QObject::tr("Qatar");
    itemQA->isoCode = "QA";
    countries.append(itemQA);
    CountriesModelItem *itemRE = new CountriesModelItem;
    itemRE->name = QObject::tr("Reunion");
    itemRE->isoCode = "RE";
    countries.append(itemRE);
    CountriesModelItem *itemRO = new CountriesModelItem;
    itemRO->name = QObject::tr("Romania");
    itemRO->isoCode = "RO";
    countries.append(itemRO);
    CountriesModelItem *itemRU = new CountriesModelItem;
    itemRU->name = QObject::tr("Russian Federation");
    itemRU->isoCode = "RU";
    countries.append(itemRU);
    CountriesModelItem *itemRW = new CountriesModelItem;
    itemRW->name = QObject::tr("Rwanda");
    itemRW->isoCode = "RW";
    countries.append(itemRW);
    CountriesModelItem *itemSH = new CountriesModelItem;
    itemSH->name = QObject::tr("Saint Helena");
    itemSH->isoCode = "SH";
    countries.append(itemSH);
    CountriesModelItem *itemKN = new CountriesModelItem;
    itemKN->name = QObject::tr("Saint Kitts and Nevis");
    itemKN->isoCode = "KN";
    countries.append(itemKN);
    CountriesModelItem *itemLC = new CountriesModelItem;
    itemLC->name = QObject::tr("Saint Lucia");
    itemLC->isoCode = "LC";
    countries.append(itemLC);
    CountriesModelItem *itemPM = new CountriesModelItem;
    itemPM->name = QObject::tr("Saint Pierre and Miquelon");
    itemPM->isoCode = "PM";
    countries.append(itemPM);
    CountriesModelItem *itemVC = new CountriesModelItem;
    itemVC->name = QObject::tr("Saint Vincent and The Grenadines");
    itemVC->isoCode = "VC";
    countries.append(itemVC);
    CountriesModelItem *itemWS = new CountriesModelItem;
    itemWS->name = QObject::tr("Samoa");
    itemWS->isoCode = "WS";
    countries.append(itemWS);
    CountriesModelItem *itemSM = new CountriesModelItem;
    itemSM->name = QObject::tr("San Marino");
    itemSM->isoCode = "SM";
    countries.append(itemSM);
    CountriesModelItem *itemST = new CountriesModelItem;
    itemST->name = QObject::tr("Sao Tome and Principe");
    itemST->isoCode = "ST";
    countries.append(itemST);
    CountriesModelItem *itemSA = new CountriesModelItem;
    itemSA->name = QObject::tr("Saudi Arabia");
    itemSA->isoCode = "SA";
    countries.append(itemSA);
    CountriesModelItem *itemSN = new CountriesModelItem;
    itemSN->name = QObject::tr("Senegal");
    itemSN->isoCode = "SN";
    countries.append(itemSN);
    CountriesModelItem *itemRS = new CountriesModelItem;
    itemRS->name = QObject::tr("Serbia");
    itemRS->isoCode = "RS";
    countries.append(itemRS);
    CountriesModelItem *itemSC = new CountriesModelItem;
    itemSC->name = QObject::tr("Seychelles");
    itemSC->isoCode = "SC";
    countries.append(itemSC);
    CountriesModelItem *itemSL = new CountriesModelItem;
    itemSL->name = QObject::tr("Sierra Leone");
    itemSL->isoCode = "SL";
    countries.append(itemSL);
    CountriesModelItem *itemSG = new CountriesModelItem;
    itemSG->name = QObject::tr("Singapore");
    itemSG->isoCode = "SG";
    countries.append(itemSG);
    CountriesModelItem *itemSK = new CountriesModelItem;
    itemSK->name = QObject::tr("Slovakia");
    itemSK->isoCode = "SK";
    countries.append(itemSK);
    CountriesModelItem *itemSI = new CountriesModelItem;
    itemSI->name = QObject::tr("Slovenia");
    itemSI->isoCode = "SI";
    countries.append(itemSI);
    CountriesModelItem *itemSB = new CountriesModelItem;
    itemSB->name = QObject::tr("Solomon Islands");
    itemSB->isoCode = "SB";
    countries.append(itemSB);
    CountriesModelItem *itemSO = new CountriesModelItem;
    itemSO->name = QObject::tr("Somalia");
    itemSO->isoCode = "SO";
    countries.append(itemSO);
    CountriesModelItem *itemZA = new CountriesModelItem;
    itemZA->name = QObject::tr("South Africa");
    itemZA->isoCode = "ZA";
    countries.append(itemZA);
    CountriesModelItem *itemGS = new CountriesModelItem;
    itemGS->name = QObject::tr("South Georgia and The South Sandwich Islands");
    itemGS->isoCode = "GS";
    countries.append(itemGS);
    CountriesModelItem *itemES = new CountriesModelItem;
    itemES->name = QObject::tr("Spain");
    itemES->isoCode = "ES";
    countries.append(itemES);
    CountriesModelItem *itemLK = new CountriesModelItem;
    itemLK->name = QObject::tr("Sri Lanka");
    itemLK->isoCode = "LK";
    countries.append(itemLK);
    CountriesModelItem *itemSD = new CountriesModelItem;
    itemSD->name = QObject::tr("Sudan");
    itemSD->isoCode = "SD";
    countries.append(itemSD);
    CountriesModelItem *itemSR = new CountriesModelItem;
    itemSR->name = QObject::tr("Suriname");
    itemSR->isoCode = "SR";
    countries.append(itemSR);
    CountriesModelItem *itemSJ = new CountriesModelItem;
    itemSJ->name = QObject::tr("Svalbard and Jan Mayen");
    itemSJ->isoCode = "SJ";
    countries.append(itemSJ);
    CountriesModelItem *itemSZ = new CountriesModelItem;
    itemSZ->name = QObject::tr("Swaziland");
    itemSZ->isoCode = "SZ";
    countries.append(itemSZ);
    CountriesModelItem *itemSE = new CountriesModelItem;
    itemSE->name = QObject::tr("Sweden");
    itemSE->isoCode = "SE";
    countries.append(itemSE);
    CountriesModelItem *itemCH = new CountriesModelItem;
    itemCH->name = QObject::tr("Switzerland");
    itemCH->isoCode = "CH";
    countries.append(itemCH);
    CountriesModelItem *itemSY = new CountriesModelItem;
    itemSY->name = QObject::tr("Syrian Arab Republic");
    itemSY->isoCode = "SY";
    countries.append(itemSY);
    CountriesModelItem *itemTW = new CountriesModelItem;
    itemTW->name = QObject::tr("Taiwan, Province of China");
    itemTW->isoCode = "TW";
    countries.append(itemTW);
    CountriesModelItem *itemTJ = new CountriesModelItem;
    itemTJ->name = QObject::tr("Tajikistan");
    itemTJ->isoCode = "TJ";
    countries.append(itemTJ);
    CountriesModelItem *itemTZ = new CountriesModelItem;
    itemTZ->name = QObject::tr("Tanzania, United Republic of");
    itemTZ->isoCode = "TZ";
    countries.append(itemTZ);
    CountriesModelItem *itemTH = new CountriesModelItem;
    itemTH->name = QObject::tr("Thailand");
    itemTH->isoCode = "TH";
    countries.append(itemTH);
    CountriesModelItem *itemTL = new CountriesModelItem;
    itemTL->name = QObject::tr("Timor-leste");
    itemTL->isoCode = "TL";
    countries.append(itemTL);
    CountriesModelItem *itemTG = new CountriesModelItem;
    itemTG->name = QObject::tr("Togo");
    itemTG->isoCode = "TG";
    countries.append(itemTG);
    CountriesModelItem *itemTK = new CountriesModelItem;
    itemTK->name = QObject::tr("Tokelau");
    itemTK->isoCode = "TK";
    countries.append(itemTK);
    CountriesModelItem *itemTO = new CountriesModelItem;
    itemTO->name = QObject::tr("Tonga");
    itemTO->isoCode = "TO";
    countries.append(itemTO);
    CountriesModelItem *itemTT = new CountriesModelItem;
    itemTT->name = QObject::tr("Trinidad and Tobago");
    itemTT->isoCode = "TT";
    countries.append(itemTT);
    CountriesModelItem *itemTN = new CountriesModelItem;
    itemTN->name = QObject::tr("Tunisia");
    itemTN->isoCode = "TN";
    countries.append(itemTN);
    CountriesModelItem *itemTR = new CountriesModelItem;
    itemTR->name = QObject::tr("Turkey");
    itemTR->isoCode = "TR";
    countries.append(itemTR);
    CountriesModelItem *itemTM = new CountriesModelItem;
    itemTM->name = QObject::tr("Turkmenistan");
    itemTM->isoCode = "TM";
    countries.append(itemTM);
    CountriesModelItem *itemTC = new CountriesModelItem;
    itemTC->name = QObject::tr("Turks and Caicos Islands");
    itemTC->isoCode = "TC";
    countries.append(itemTC);
    CountriesModelItem *itemTV = new CountriesModelItem;
    itemTV->name = QObject::tr("Tuvalu");
    itemTV->isoCode = "TV";
    countries.append(itemTV);
    CountriesModelItem *itemUG = new CountriesModelItem;
    itemUG->name = QObject::tr("Uganda");
    itemUG->isoCode = "UG";
    countries.append(itemUG);
    CountriesModelItem *itemUA = new CountriesModelItem;
    itemUA->name = QObject::tr("Ukraine");
    itemUA->isoCode = "UA";
    countries.append(itemUA);
    CountriesModelItem *itemAE = new CountriesModelItem;
    itemAE->name = QObject::tr("United Arab Emirates");
    itemAE->isoCode = "AE";
    countries.append(itemAE);
    CountriesModelItem *itemGB = new CountriesModelItem;
    itemGB->name = QObject::tr("United Kingdom");
    itemGB->isoCode = "GB";
    countries.append(itemGB);
    CountriesModelItem *itemUS = new CountriesModelItem;
    itemUS->name = QObject::tr("United States");
    itemUS->isoCode = "US";
    countries.append(itemUS);
    CountriesModelItem *itemUM = new CountriesModelItem;
    itemUM->name = QObject::tr("United States Minor Outlying Islands");
    itemUM->isoCode = "UM";
    countries.append(itemUM);
    CountriesModelItem *itemUY = new CountriesModelItem;
    itemUY->name = QObject::tr("Uruguay");
    itemUY->isoCode = "UY";
    countries.append(itemUY);
    CountriesModelItem *itemUZ = new CountriesModelItem;
    itemUZ->name = QObject::tr("Uzbekistan");
    itemUZ->isoCode = "UZ";
    countries.append(itemUZ);
    CountriesModelItem *itemVU = new CountriesModelItem;
    itemVU->name = QObject::tr("Vanuatu");
    itemVU->isoCode = "VU";
    countries.append(itemVU);
    CountriesModelItem *itemVE = new CountriesModelItem;
    itemVE->name = QObject::tr("Venezuela");
    itemVE->isoCode = "VE";
    countries.append(itemVE);
    CountriesModelItem *itemVN = new CountriesModelItem;
    itemVN->name = QObject::tr("Viet Nam");
    itemVN->isoCode = "VN";
    countries.append(itemVN);
    CountriesModelItem *itemVG = new CountriesModelItem;
    itemVG->name = QObject::tr("Virgin Islands, British");
    itemVG->isoCode = "VG";
    countries.append(itemVG);
    CountriesModelItem *itemVI = new CountriesModelItem;
    itemVI->name = QObject::tr("Virgin Islands, U.S.");
    itemVI->isoCode = "VI";
    countries.append(itemVI);
    CountriesModelItem *itemWF = new CountriesModelItem;
    itemWF->name = QObject::tr("Wallis and Futuna");
    itemWF->isoCode = "WF";
    countries.append(itemWF);
    CountriesModelItem *itemEH = new CountriesModelItem;
    itemEH->name = QObject::tr("Western Sahara");
    itemEH->isoCode = "EH";
    countries.append(itemEH);
    CountriesModelItem *itemYE = new CountriesModelItem;
    itemYE->name = QObject::tr("Yemen");
    itemYE->isoCode = "YE";
    countries.append(itemYE);
    CountriesModelItem *itemZM = new CountriesModelItem;
    itemZM->name = QObject::tr("Zambia");
    itemZM->isoCode = "ZM";
    countries.append(itemZM);
    CountriesModelItem *itemZW = new CountriesModelItem;
    itemZW->name = QObject::tr("Zimbabwe");
    itemZW->isoCode = "ZW";
    countries.append(itemZW);


    data = countries;
    data.prepend(all);
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
                if (item->name.toLower().startsWith(filter.toLower())) {
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
