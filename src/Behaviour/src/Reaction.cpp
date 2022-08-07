#include "Reaction.hpp"

namespace Evolution
{
    namespace Behaviour
    {
        Reaction &Reaction::GetInstance()
        {
            static Reaction react;
            return react;
        }

        ReactionType Reaction::React(std::shared_ptr<Evolution::Organism::IOrganismEntity> organism, std::shared_ptr<Evolution::Organism::IOrganismEntity> target)
        {
            auto attr = organism->GetAttributes();
            ReactionType react;
            switch (attr.type)
            {
            case Evolution::Organism::OrganismType::CARNIVORE:
                react = Carnivore(attr, target->GetAttributes());
                break;

            case Evolution::Organism::OrganismType::HERBIVORE:
                react = Herbivore(attr, target->GetAttributes());
                break;

            default:
                react = ReactionType::INVALID;
                break;
            }

            return react;
        }

        ReactionType Reaction::Carnivore(Evolution::Organism::Attributes organism, Evolution::Organism::Attributes target)
        {
            if (target.type == organism.type)
            {
            }
            else
            {
            }

            return ReactionType::IGNORE;
        }

        ReactionType Reaction::Herbivore(Evolution::Organism::Attributes organism, Evolution::Organism::Attributes target)
        {
            if (target.type == Evolution::Organism::OrganismType::CARNIVORE)
            {
                if (organism.energy < target.energy)
                    return ReactionType::RUN;

                else
                    return ReactionType::IGNORE;
            }
            else
            {
                return ReactionType::GROUP;
            }
        }
    }
}