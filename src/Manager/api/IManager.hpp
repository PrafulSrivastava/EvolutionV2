#ifndef IMANAGER_HPP
#define IMANAGER_HPP

#include "IEntity.hpp"
#include "IConfig.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Reaction.hpp"

namespace Evolution
{
    namespace Manager
    {

        class IManager
        {
        public:
            virtual void RunGameLoop() = 0;
            virtual void Shutdown() = 0;

        protected:
            std::shared_ptr<sf::RenderWindow> m_window{nullptr};
        };
    }
}

#endif