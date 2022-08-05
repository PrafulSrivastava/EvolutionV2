#ifndef BACTERIA_HPP
#define BACTERIA_HPP

#include "IOrganismEntity.hpp"
#include <memory>

namespace Evolution::Organism
{
    class Bacteria : public IOrganismEntity
    {
    public:
        Bacteria();
        ~Bacteria() = default;
        Bacteria(const Bacteria &) = default;
        Bacteria &operator=(const Bacteria &) = default;
        Bacteria(Bacteria &&) = default;
        Bacteria &operator=(Bacteria &&) = default;

        void OnCollision(Species) override;
        void Spawn() override;
        void Destroy() override;
        void RunMainLoop() override;

    private:
    };

}

#endif