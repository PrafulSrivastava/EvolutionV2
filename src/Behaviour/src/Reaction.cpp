#include "Reaction.hpp"
#include "CUtility.hpp"

#include <iostream>

namespace Evolution
{
    namespace Behaviour
    {
        Reaction &Reaction::GetInstance()
        {
            static Reaction react;
            return react;
        }

        ReactionType Reaction::FetchReaction(ReactionInfo &reactInfo)
        {

            ReactionType react{};
            switch (reactInfo.org->type)
            {
            case Evolution::Organism::SpeciesType::CARNIVORE:
                react = FetchCarnivoreReaction(reactInfo);
                break;

            case Evolution::Organism::SpeciesType::HERBIVORE:
                react = FetchHerbivoreReaction(reactInfo);
                break;

            case Evolution::Organism::SpeciesType::OMNIVORE:
                react = FetchOmnivoreReaction(reactInfo);
                break;

            default:
                react = ReactionType::INVALID;
                break;
            }

            return react;
        }

        Resolution Reaction::GetCapability(std::shared_ptr<Evolution::Organism::Attributes> attr)
        {
            return 0.4 * (attr->aggression + attr->energy) + 0.6 * (attr->speed + attr->stamina);
        }

        bool Reaction::AmICapable(ReactionInfo &reactInfo)
        {
            bool response = false;

            if (GetCapability(reactInfo.org) > GetCapability(reactInfo.target))
            {
                response = true;
            }

            return response;
        }

        ReactionType Reaction::FetchCarnivoreReaction(ReactionInfo &reactInfo)
        {
            ReactionType reaction = ReactionType::IGNORE;

            if (reactInfo.target->subType == Organism::SpeciesSubType::VEGETATION)
            {
                return reaction;
            }

            bool capable = AmICapable(reactInfo);
            switch (reactInfo.org->state)
            {
            case Organism::EnergyBand::LOW:
            {
                // Desperate to increase health
                if (capable)
                {
                    // reaction = ReactionType::CONSUME;
                    reaction = ReactionType::KILL;
                }
                else
                {
                    if (reactInfo.targetReaction == ReactionType::KILL)
                        reaction = ReactionType::RUN;
                }

                break;
            }
            case Organism::EnergyBand::MEDIUM:
            {
                if (reactInfo.targetReaction != ReactionType::KILL)
                {
                    if (capable)
                    {
                        reaction = ReactionType::KILL;
                    }
                }
            }
            case Organism::EnergyBand::HIGH:
            {
                // if target seen is coming towards you to kill
                if (reactInfo.targetReaction == ReactionType::KILL)
                {
                    if (capable)
                    {
                        reaction = ReactionType::FIGHT;
                    }
                    else
                    {
                        reaction = ReactionType::RUN;
                    }
                }

                break;
            }
            default:
                reaction = ReactionType::IGNORE;
                break;
            }

            return reaction;
        }

        ReactionType Reaction::FetchHerbivoreReaction(ReactionInfo &reactInfo)
        {
            ReactionType reaction = ReactionType::IGNORE;

            bool capable = AmICapable(reactInfo);

            switch (reactInfo.target->type)
            {
            case Organism::SpeciesType::HERBIVORE:
                reaction = ReactionType::GROUP;
                break;
            case Organism::SpeciesType::CARNIVORE:
            case Organism::SpeciesType::OMNIVORE:
            {
                if (reactInfo.targetReaction == ReactionType::KILL)
                {
                    if (capable)
                    {
                        reaction = ReactionType::FIGHT;
                    }
                    else
                    {
                        reaction = ReactionType::RUN;
                    }
                }
                else
                {
                    if (capable)
                    {
                        reaction = ReactionType::IGNORE;
                    }
                    else
                    {
                        reaction = ReactionType::RUN;
                    }
                }
                break;
            }
            case Organism::SpeciesType::POI:
                if (reactInfo.org->state != Organism::EnergyBand::HIGH)
                    reaction = ReactionType::KILL;
                break;
            }

            return reaction;
        }

        ReactionType Reaction::FetchOmnivoreReaction(ReactionInfo &reactInfo)
        {

            ReactionType reaction = ReactionType::INVALID;

            switch (reactInfo.target->type)
            {
            case Organism::SpeciesType::HERBIVORE:
                reaction = ReactionType::KILL;
                break;
            case Organism::SpeciesType::CARNIVORE:
                reaction = ReactionType::FIGHT;
                break;
            case Organism::SpeciesType::OMNIVORE:
                reaction = ReactionType::GROUP;
                break;
            }
            return reaction;
        }

        std::vector<Movement::MovementOperation> Reaction::ReactCarnivore(Behaviour::ReactionType reaction)
        {
            std::vector<Movement::MovementOperation> operations;
            switch (reaction)
            {
            case Behaviour::ReactionType::KILL:
                operations.push_back(Movement::MovementOperation::IncrementSpeed);
                operations.push_back(Movement::MovementOperation::ChangeMotionToKill);
                break;

            case Behaviour::ReactionType::IGNORE:
                operations.push_back(Movement::MovementOperation::ChangeMotionToIgnore);
                operations.push_back(Movement::MovementOperation::RotateByRandom);
                break;

            case Behaviour::ReactionType::FIGHT:
                operations.push_back(Movement::MovementOperation::ChangeMotionToFight);
                operations.push_back(Movement::MovementOperation::IncrementSpeed);
                break;

            default:
                break;
            }

            return operations;
        }

        std::vector<Movement::MovementOperation> Reaction::ReactHerbivore(Behaviour::ReactionType reaction)
        {
            std::vector<Movement::MovementOperation> operations;
            switch (reaction)
            {

            case Behaviour::ReactionType::IGNORE:
                operations.push_back(Movement::MovementOperation::ChangeMotionToIgnore);
                operations.push_back(Movement::MovementOperation::RotateByRandom);
                break;

            case Behaviour::ReactionType::RUN:
                operations.push_back(Movement::MovementOperation::ChangeMotionToRun);
                operations.push_back(Movement::MovementOperation::RotateBy180);
                // operations.push_back(Movement::MovementOperation::IncrementSpeed);
                break;

            case Behaviour::ReactionType::GROUP:
                operations.push_back(Movement::MovementOperation::ChangeMotionToGroup);
                // operations.push_back(Movement::MovementOperation::DecrementSpeed);
                break;

            case Behaviour::ReactionType::FIGHT:
                operations.push_back(Movement::MovementOperation::ChangeMotionToFight);
                operations.push_back(Movement::MovementOperation::IncrementSpeed);
                break;

            case Behaviour::ReactionType::KILL:
                operations.push_back(Movement::MovementOperation::ChangeMotionToKill);
                break;

            default:
                break;
            }

            return operations;
        }

        std::vector<Movement::MovementOperation> Reaction::ReactOmnivore(Behaviour::ReactionType reaction)
        {
            std::vector<Movement::MovementOperation> operations;
            switch (reaction)
            {
            case Behaviour::ReactionType::KILL:
                operations.push_back(Movement::MovementOperation::ChangeMotionToKill);
                break;

            case Behaviour::ReactionType::IGNORE:
                operations.push_back(Movement::MovementOperation::ChangeMotionToIgnore);
                operations.push_back(Movement::MovementOperation::RotateByRandom);
                break;

            case Behaviour::ReactionType::RUN:
                operations.push_back(Movement::MovementOperation::ChangeMotionToRun);
                operations.push_back(Movement::MovementOperation::IncrementSpeed);
                operations.push_back(Movement::MovementOperation::RotateBy90);
                break;

            case Behaviour::ReactionType::GROUP:
                operations.push_back(Movement::MovementOperation::ChangeMotionToGroup);
                operations.push_back(Movement::MovementOperation::DecrementSpeed);
                break;

            case Behaviour::ReactionType::FIGHT:
                operations.push_back(Movement::MovementOperation::ChangeMotionToFight);
                operations.push_back(Movement::MovementOperation::IncrementSpeed);
                break;

            default:
                break;
            }

            return operations;
        }

        std::vector<Movement::MovementOperation> Reaction::React(Evolution::Organism::SpeciesType type, Behaviour::ReactionType reaction)
        {
            std::vector<Movement::MovementOperation> operations;
            switch (type)
            {
            case Evolution::Organism::SpeciesType::CARNIVORE:
                operations = std::move(ReactCarnivore(reaction));
                break;

            case Evolution::Organism::SpeciesType::HERBIVORE:
                operations = std::move(ReactHerbivore(reaction));
                break;

            case Evolution::Organism::SpeciesType::OMNIVORE:
                operations = std::move(ReactOmnivore(reaction));
                break;

            default:
                break;
            }

            return operations;
        }

    }
}