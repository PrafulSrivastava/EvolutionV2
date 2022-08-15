#include "Reaction.hpp"
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

        ReactionType Reaction::FetchReaction(std::shared_ptr<Evolution::Organism::Attributes> organismAttributes, std::shared_ptr<Evolution::Organism::Attributes> targetAttributes)
        {

            ReactionType react;
            switch (organismAttributes->type)
            {
            case Evolution::Organism::OrganismType::CARNIVORE:
                react = FetchCarnivoreReaction(organismAttributes, targetAttributes);
                break;

            case Evolution::Organism::OrganismType::HERBIVORE:
                react = FetchHerbivoreReaction(organismAttributes, targetAttributes);
                break;

            case Evolution::Organism::OrganismType::OMNIVORE:
                react = FetchOmnivoreReaction(organismAttributes, targetAttributes);
                break;

            default:
                react = ReactionType::INVALID;
                break;
            }

            return react;
        }

        ReactionType Reaction::FetchCarnivoreReaction(std::shared_ptr<Evolution::Organism::Attributes> organismAttributes, std::shared_ptr<Evolution::Organism::Attributes> targetAttributes)
        {
            ReactionType reaction = ReactionType::INVALID;

            switch (targetAttributes->type)
            {
            case Organism::OrganismType::HERBIVORE:
                reaction = ReactionType::KILL;
                break;
            case Organism::OrganismType::CARNIVORE:
                reaction = ReactionType::IGNORE;
                break;
            case Organism::OrganismType::OMNIVORE:
                reaction = ReactionType::FIGHT;
                break;
            }
            return reaction;
        }

        ReactionType Reaction::FetchHerbivoreReaction(std::shared_ptr<Evolution::Organism::Attributes> organismAttributes, std::shared_ptr<Evolution::Organism::Attributes> targetAttributes)
        {

            ReactionType reaction = ReactionType::INVALID;

            switch (targetAttributes->type)
            {
            case Organism::OrganismType::HERBIVORE:
                reaction = ReactionType::GROUP;
                break;
            case Organism::OrganismType::CARNIVORE:
                reaction = ReactionType::RUN;
                break;
            case Organism::OrganismType::OMNIVORE:
                reaction = ReactionType::FIGHT;
                break;
            }
            return reaction;
        }

        ReactionType Reaction::FetchOmnivoreReaction(std::shared_ptr<Evolution::Organism::Attributes> organismAttributes, std::shared_ptr<Evolution::Organism::Attributes> targetAttributes)
        {

            ReactionType reaction = ReactionType::INVALID;

            switch (targetAttributes->type)
            {
            case Organism::OrganismType::HERBIVORE:
                reaction = ReactionType::KILL;
                break;
            case Organism::OrganismType::CARNIVORE:
                reaction = ReactionType::FIGHT;
                break;
            case Organism::OrganismType::OMNIVORE:
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
                operations.push_back(Movement::MovementOperation::IncrementSpeed);
                break;

            case Behaviour::ReactionType::GROUP:
                operations.push_back(Movement::MovementOperation::ChangeMotionToGroup);
                // operations.push_back(Movement::MovementOperation::DecrementSpeed);
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
                // operations.push_back(Movement::MovementOperation::DecrementSpeed);
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

        std::vector<Movement::MovementOperation> Reaction::React(Evolution::Organism::OrganismType type, Behaviour::ReactionType reaction)
        {
            std::vector<Movement::MovementOperation> operations;
            switch (type)
            {
            case Evolution::Organism::OrganismType::CARNIVORE:
                operations = std::move(ReactCarnivore(reaction));
                break;

            case Evolution::Organism::OrganismType::HERBIVORE:
                operations = std::move(ReactHerbivore(reaction));
                break;

            case Evolution::Organism::OrganismType::OMNIVORE:
                operations = std::move(ReactOmnivore(reaction));
                break;

            default:
                break;
            }

            return operations;
        }

    }
}