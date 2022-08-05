#ifndef IMANAGER_HPP
#define IMANAGER_HPP

#include "IEntity.hpp"
#include "IConfig.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace Evolution
{
    namespace Manager
    {

        class IManager
        {
        public:
            virtual void RunGameLoop() = 0;

        protected:
            std::shared_ptr<sf::RenderWindow> m_window;
        };
    }
}

#endif