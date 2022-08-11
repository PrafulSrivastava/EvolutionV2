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

        ReactionType Reaction::React(Evolution::Organism::Attributes organismAttributes, Evolution::Organism::Attributes targetAttributes)
        {

            ReactionType react;
            switch (organismAttributes.type)
            {
            case Evolution::Organism::OrganismType::CARNIVORE:
                react = Carnivore(organismAttributes, targetAttributes);
                break;

            case Evolution::Organism::OrganismType::HERBIVORE:
                react = Herbivore(organismAttributes, targetAttributes);
                break;

            default:
                react = ReactionType::INVALID;
                break;
            }

            return react;
        }

        ReactionType Reaction::Carnivore(Evolution::Organism::Attributes organismAttributes, Evolution::Organism::Attributes targetAttributes)
        {
            if (targetAttributes.type == organismAttributes.type)
            {
            }
            else
            {
            }

            return ReactionType::IGNORE;
        }

        ReactionType Reaction::Herbivore(Evolution::Organism::Attributes organismAttributes, Evolution::Organism::Attributes targetAttributes)
        {
            if (targetAttributes.type == Evolution::Organism::OrganismType::CARNIVORE)
            {
                if (organismAttributes.energy < targetAttributes.energy)
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