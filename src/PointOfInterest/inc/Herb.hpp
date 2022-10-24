#ifndef HERBS_HPP
#define HERBS_HPP

#include "IPointOfInterest.hpp"
#include <memory>

namespace Evolution::PointOfInterest
{
    class Herb : public IPointOfInterestEntity
    {
    public:
        Herb(Organism::SpeciesType);
        ~Herb() = default;
        Herb(const Herb &) = default;
        Herb &operator=(const Herb &) = default;
        Herb(Herb &&) = default;
        Herb &operator=(Herb &&) = default;

        void SetEntityId(NFResolution32) override;
        void Spawn() override;
        void Destroy() override;
        void RunMainLoop() override;

    private:
    };
}

#endif