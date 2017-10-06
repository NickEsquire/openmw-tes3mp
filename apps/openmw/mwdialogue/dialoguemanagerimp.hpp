#ifndef GAME_MWDIALOG_DIALOGUEMANAGERIMP_H
#define GAME_MWDIALOG_DIALOGUEMANAGERIMP_H

#include "../mwbase/dialoguemanager.hpp"

#include <map>
#include <set>

#include <components/compiler/streamerrorhandler.hpp>
#include <components/translation/translation.hpp>

#include "../mwworld/ptr.hpp"

#include "../mwscript/compilercontext.hpp"

namespace ESM
{
    struct Dialogue;
}

namespace MWDialogue
{
    class DialogueManager : public MWBase::DialogueManager
    {
            std::set<std::string> mKnownTopics;// Those are the topics the player knows.

            // Modified faction reactions. <Faction1, <Faction2, Difference> >
            typedef std::map<std::string, std::map<std::string, int> > ModFactionReactionMap;
            ModFactionReactionMap mChangedFactionReaction;

            std::set<std::string> mActorKnownTopics;

            Translation::Storage& mTranslationDataStorage;
            MWScript::CompilerContext mCompilerContext;
            std::ostream mErrorStream;
            Compiler::StreamErrorHandler mErrorHandler;

            MWWorld::Ptr mActor;
            bool mTalkedTo;

            int mChoice;
            std::string mLastTopic; // last topic ID, lowercase
            bool mIsInChoice;
            bool mGoodbye;

            std::vector<std::pair<std::string, int> > mChoices;

            float mTemporaryDispositionChange;
            float mPermanentDispositionChange;

            void parseText (const std::string& text);

            void updateActorKnownTopics();
            void updateGlobals();

            bool compile (const std::string& cmd, std::vector<Interpreter::Type_Code>& code, const MWWorld::Ptr& actor);
            void executeScript (const std::string& script, const MWWorld::Ptr& actor);

            Response executeTopic (const std::string& topic);

            const ESM::Dialogue* searchDialogue(const std::string& id);

        public:

            DialogueManager (const Compiler::Extensions& extensions, Translation::Storage& translationDataStorage);

            virtual void clear();

            virtual bool isInChoice() const;

            virtual bool startDialogue (const MWWorld::Ptr& actor, Response& response);

            std::list<std::string> getAvailableTopics();

            virtual void addTopic (const std::string& topic);

            /*
                Start of tes3mp addition

                Make it possible to check whether a topic is known by the player from elsewhere
                in the code
            */
            virtual bool isNewTopic(const std::string& topic);
            /*
                End of tes3mp addition
            */

            virtual void addChoice (const std::string& text,int choice);
            const std::vector<std::pair<std::string, int> >& getChoices();

            virtual bool isGoodbye();

            virtual void goodbye();

            virtual bool checkServiceRefused (Response& response);

            virtual void say(const MWWorld::Ptr &actor, const std::string &topic);

            //calbacks for the GUI
            virtual Response keywordSelected (const std::string& keyword);
            virtual void goodbyeSelected();
            virtual Response questionAnswered (int answer);

            virtual Response persuade (int type);
            virtual int getTemporaryDispositionChange () const;

            /// @note This change is temporary and gets discarded when dialogue ends.
            virtual void applyDispositionChange (int delta);

            virtual int countSavedGameRecords() const;

            virtual void write (ESM::ESMWriter& writer, Loading::Listener& progress) const;

            virtual void readRecord (ESM::ESMReader& reader, uint32_t type);

            /// Changes faction1's opinion of faction2 by \a diff.
            virtual void modFactionReaction (const std::string& faction1, const std::string& faction2, int diff);

            virtual void setFactionReaction (const std::string& faction1, const std::string& faction2, int absolute);

            /// @return faction1's opinion of faction2
            virtual int getFactionReaction (const std::string& faction1, const std::string& faction2) const;

            /// Removes the last added topic response for the given actor from the journal
            virtual void clearInfoActor (const MWWorld::Ptr& actor) const;
    };
}

#endif
