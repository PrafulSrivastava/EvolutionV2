#ifndef BACTERIA_HPP
#define BACTERIA_HPP

#include "IOrganismEntity.hpp"

namespace Evolution::Organism
{
    class Bacteria : public IOrganismEntity
    {
    public:
        Bacteria();
        ~Bacteria();

        void OnCollision(Species) override;
        void Spawn() override;
        void Destroy() override;

    private:
    };
}

#endif