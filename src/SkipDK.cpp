/*
 *MIT License
 *
 *Copyright (c) 2023 Azerothcore
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *SOFTWARE.
 *
 * Skip Death Knight Module
 * Original Module From Single Player Project Consolidated Skip Module
 * Rewritten for TC 335 By Single Player Project Developer MDic
 * Original Concept from conanhun513
 * Assistance and Review by JinnaiX
 * Modified for Azerothcore
 */

#include "AccountMgr.h"
#include "skipdk_loader.h"
#include "Chat.h"
#include "Common.h"
#include "Config.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SharedDefines.h"
#include "World.h"
#include "WorldSession.h"

using namespace Acore::ChatCommands;


static void HandleDKGO(Player* player, Quest const* quest) {

    player->RewardQuest(quest, 0, player);

}

void Azerothcore_skip_deathknight_HandleSkip(Player* player)
{
    player->AddItem(6948, true); //Hearthstone
  
    // these are all the starter quests that award talent points, quest items, or spells
    
    int STARTER_QUESTS[32] =
      { 12593, 12619, 12842, 12848, 12636,
        12641, 12657, 12850, 12670, 12678,
        12680, 12687, 12679, 12733, 12697, 
        12698, 12700, 12701, 12706, 12714,
        12715, 12719, 12720, 12722, 12716, 
        12717, 12723, 12724, 12725, 12727,
        12728, -1};

    int STARTER_QUESTS_CONTINUED[11] = { 12751, 12754, 12755, 12756, 12757, 12778, 12779, 12800, 12801, 13165, 13166 };

    int specialSurpriseQuestId = -1; // IF PROCESSED CAUSES WORLDSERVER

    switch (player->getRace())
    {
    case RACE_TAUREN:
        specialSurpriseQuestId = 12739;
        break;
    case RACE_HUMAN:
        specialSurpriseQuestId = 12742;
        break;
    case RACE_NIGHTELF:
        specialSurpriseQuestId = 12743;
        break;
    case RACE_DWARF:
        specialSurpriseQuestId = 12744;
        break;
    case RACE_GNOME:
        specialSurpriseQuestId = 12745;
        break;
    case RACE_DRAENEI:
        specialSurpriseQuestId = 12746;
        break;
    case RACE_BLOODELF:
        specialSurpriseQuestId = 12747;
        break;
    case RACE_ORC:
        specialSurpriseQuestId = 12748;
        break;
    case RACE_TROLL:
        specialSurpriseQuestId = 12749;
        break;
    case RACE_UNDEAD_PLAYER:
        specialSurpriseQuestId = 12750;
        break;
    case RACE_GOBLIN:
        specialSurpriseQuestId = 12748; // ORC
        break;
    case RACE_WORGEN:
        specialSurpriseQuestId = 12743; // NIGHTELF
        break;
    }

    STARTER_QUESTS[31] = specialSurpriseQuestId;

    Sleep(3500); // SLEEP
 
    for (int questId : STARTER_QUESTS)
    {
        
        Quest const* curQuest = sObjectMgr->GetQuestTemplate(questId);

        if (player->GetQuestStatus(questId) == QUEST_STATUS_NONE)
        {
            
            player->AddQuest(curQuest, nullptr);

        }


        HandleDKGO(player, curQuest);
    }


    for (int questIdCont : STARTER_QUESTS_CONTINUED)
    {

       Quest const* curContQuest = sObjectMgr->GetQuestTemplate(questIdCont);

        if (player->GetQuestStatus(questIdCont) == QUEST_STATUS_NONE)
        {

            player->AddQuest(curContQuest, nullptr);

        }

        HandleDKGO(player, curContQuest);
    }

    
    if (player->GetTeamId() == TEAM_ALLIANCE) {

        Quest const* curQuest = sObjectMgr->GetQuestTemplate(13188);

        if (player->GetQuestStatus(13188) == QUEST_STATUS_NONE)
        {

            player->AddQuest(curQuest, nullptr);

        }

        HandleDKGO(player, curQuest);
    }
    else {
        Quest const* curQuest = sObjectMgr->GetQuestTemplate(13189);

        if (player->GetQuestStatus(13189) == QUEST_STATUS_NONE)
        {

            player->AddQuest(curQuest, nullptr);

        }

        HandleDKGO(player, curQuest);
    }
    

    //these are alternate reward items from quest 12679, item 39320 is chosen by default as the reward
    player->AddItem(38664, true);//Sky Darkener's Shroud of the Unholy
    player->AddItem(39322, true);//Shroud of the North Wind

    //these are alternate reward items from quest 12801, item 38633 is chosen by default as the reward
    player->AddItem(38632, true);//Greatsword of the Ebon Blade

    int DKL = 58;
    if (player->GetLevel() <= DKL)
    {
        //GiveLevel updates character properties more thoroughly than SetLevel
        player->GiveLevel(DKL);
    }

    player->learnSpell(49998, false, false); // Death Strike rank 1
    player->learnSpell(47528, false, false); // Mind Freeze
    player->learnSpell(46584, false, false); // Raise Dead
    player->learnSpell(48263, false, false); // Frost Presence
    player->learnSpell(45524, false, false); // Chains of Ice
    player->learnSpell(48721, false, false); // Blood Boil rank 1
    player->learnSpell(50842, false, false); // Pestilence
    player->learnSpell(53342, false, false); // Rune of Spellshattering
    player->learnSpell(54447, false, false); // Rune of Spellbreaking
 
    //Don't need to save all players, just current
    player->SaveToDB(false, false);
    
    WorldLocation Aloc = WorldLocation(0, -8866.55f, 671.39f, 97.90f, 5.27f);// Stormwind
    WorldLocation Hloc = WorldLocation(1, 1637.62f, -4440.22f, 15.78f, 2.42f);// Orgrimmar
    /*
    if (player->GetTeamId() == TEAM_ALLIANCE)
    {
        //Sleep(5000);
        player->TeleportTo(0, -8833.37f, 628.62f, 94.00f, 1.06f);//Stormwind
        player->SetHomebind(Aloc, 1637);// Stormwind Homebind location
    }
    else
    {
        //Sleep(5000);
        player->TeleportTo(1, 1569.59f, -4397.63f, 7.70f, 0.54f);//Orgrimmar
        player->SetHomebind(Hloc, 1653);// Orgrimmar Homebind location
    }
    */

}

class AzerothCore_skip_deathknight_announce : public PlayerScript
{
public:
    AzerothCore_skip_deathknight_announce() : PlayerScript("AzerothCore_skip_deathknight_announce") { }

    void OnPlayerLogin(Player* Player)
    {
        //ChatHandler(Player->GetSession()).SendSysMessage("|cff4CFF00 DK SKIP ACTIVE|r.");
    }
};

class AzerothCore_skip_deathknight : public PlayerScript
{
public:
    AzerothCore_skip_deathknight() : PlayerScript("AzerothCore_skip_deathknight") {}

    void OnPlayerFirstLogin(Player* player) override
    {
        if (player->GetAreaId() == 4342)
        {
                Azerothcore_skip_deathknight_HandleSkip(player); 
        }
    }
};

void AddSkipDKScripts()
{
    new AzerothCore_skip_deathknight_announce;
    new AzerothCore_skip_deathknight;
}
