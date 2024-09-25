/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once
    #include <iostream>
    #include <memory>
    #include "../IRenderSystem/IRenderSystem.hpp"
    #include <unistd.h>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>

/**
 * @file RenderSystem.hpp
 * @brief Déclaration de la classe RenderSystem du namespace RType.
 */

namespace RType
{
    /**
     * @class RenderSystem
     * @brief Système de rendu pour le jeu RType.
     *
     * Cette classe gère les opérations de rendu, telles que la gestion des fenêtres,
     * l'affichage des sprites, des textes, et la gestion des événements liés à l'interface graphique.
     */
    class RenderSystem : public RType::IRenderSystem {
        public:

            /**
             * @brief Constructeur de la classe RenderSystem.
             *
             * Initialise une fenêtre graphique avec une résolution de 1920x1080 pixels.
             */
            RenderSystem();

            /**
             * @brief Destructeur de la classe RenderSystem.
             */
            ~RenderSystem();

        public:

            /**
             * @brief Récupère les entrées utilisateur (clavier, souris, etc.).
             * @return RType::Event Événement capturé.
             *
             * Cette méthode permet de capturer les événements provenant de l'utilisateur, 
             * tels que les touches du clavier ou les mouvements de la souris.
             */
            RType::Event getInput() override;

            /**
             * @brief Efface la fenêtre pour le prochain rendu.
             *
             * Cette méthode doit être appelée avant chaque cycle de rendu pour effacer le contenu
             * de la fenêtre et préparer l'affichage d'un nouveau frame.
             */
            void clearWindow() override;

            /**
             * @brief Met à jour la fenêtre après le rendu.
             *
             * Cette méthode permet d'afficher le contenu de la fenêtre après le cycle de rendu.
             */
            void updateWindow() override;

            /**
             * @brief Affiche un texte à l'écran.
             *
             * Cette méthode permet de dessiner du texte sur la fenêtre de rendu.
             */
            void drawText() override;

            /**
             * @brief Affiche un sprite à l'écran.
             *
             * Cette méthode permet de dessiner un sprite (image 2D) sur la fenêtre de rendu.
             */
            void drawSprite() override;

            /**
             * @brief Bascule la fenêtre en mode plein écran.
             *
             * Permet de passer la fenêtre en mode plein écran ou de revenir en mode fenêtre normale.
             */
            void FullScreenWindow() override;

            bool isWindowOpen() const { return _window.isOpen(); } 

            sf::RenderWindow _window;  ///< Fenêtre de rendu SFML.

        private:
            bool _isFullScreen;        ///< Indique si la fenêtre est en mode plein écran.
    };
}
