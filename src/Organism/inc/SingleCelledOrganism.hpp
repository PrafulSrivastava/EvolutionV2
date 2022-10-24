#ifndef SINGLECELLEDORGANISM_HPP
#define SINGLECELLEDORGANISM_HPP

#include "IOrganismEntity.hpp"
#include <memory>

namespace Evolution::Organism
{
    class SingleCelledOrganism : public IOrganismEntity
    {
    public:
        SingleCelledOrganism(Organism::SpeciesType);
        ~SingleCelledOrganism() = default;
        SingleCelledOrganism(const SingleCelledOrganism &) = default;
        SingleCelledOrganism &operator=(const SingleCelledOrganism &) = default;
        SingleCelledOrganism(SingleCelledOrganism &&) = default;
        SingleCelledOrganism &operator=(SingleCelledOrganism &&) = default;

        void SetEntityId(NFResolution32) override;
        void Spawn() override;
        void Destroy() override;
        void RunMainLoop() override;

    private:
    };

}

#endif