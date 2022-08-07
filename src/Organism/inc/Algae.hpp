#ifndef ALGAE_HPP
#define ALGAE_HPP

#include "IOrganismEntity.hpp"
#include <memory>

namespace Evolution::Organism
{
    class Algae : public IOrganismEntity
    {
    public:
        Algae();
        ~Algae() = default;
        Algae(const Algae &) = default;
        Algae &operator=(const Algae &) = default;
        Algae(Algae &&) = default;
        Algae &operator=(Algae &&) = default;

        void OnCollision(Species) override;
        void Spawn() override;
        void Destroy() override;
        void RunMainLoop() override;

    private:
    };

}

#endif