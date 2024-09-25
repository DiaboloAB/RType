/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include <iostream>
    #include <memory>
    #include "../common/Event.hpp"

/**
 * @file IRenderSystem.hpp
 * @brief Interface de rendu pour le jeu RType.
 */

namespace RType
{
    /**
     * @class IRenderSystem
     * @brief Interface pour la gestion du système de rendu.
     *
     * Cette interface définit les méthodes nécessaires pour tout système de rendu
     * utilisé dans le jeu RType. Les classes dérivées doivent implémenter ces méthodes
     * pour gérer l'affichage, les entrées utilisateur, ainsi que le contrôle de la fenêtre.
     */
    class IRenderSystem {

        public:
            /**
             * @brief Méthode virtuelle pure pour récupérer les entrées utilisateur.
             * @return RType::Event Événement utilisateur capturé.
             *
             * Cette méthode doit être implémentée pour capturer les entrées de l'utilisateur
             * (clavier, souris, etc.).
             */
            virtual RType::Event getInput() = 0;

            /**
             * @brief Méthode virtuelle pure pour effacer la fenêtre avant un nouveau rendu.
             *
             * Cette méthode doit être implémentée pour effacer le contenu de la fenêtre,
             * permettant ainsi de préparer un nouveau frame à afficher.
             */
            virtual void clearWindow() = 0;

            /**
             * @brief Méthode virtuelle pure pour mettre à jour la fenêtre après le rendu.
             *
             * Doit être implémentée pour gérer l'affichage à l'écran après avoir effectué
             * toutes les opérations de rendu.
             */
            virtual void updateWindow() = 0;

            /**
             * @brief Méthode virtuelle pure pour afficher un sprite sur la fenêtre.
             *
             * Cette méthode doit être implémentée pour dessiner des images ou des sprites
             * dans la fenêtre de rendu.
             */
            virtual void drawSprite() = 0;

            /**
             * @brief Méthode virtuelle pure pour afficher un texte sur la fenêtre.
             *
             * Doit être implémentée pour gérer l'affichage de textes (comme des scores ou des informations)
             * à l'écran.
             */
            virtual void drawText() = 0;

            /**
             * @brief Méthode virtuelle pure pour basculer la fenêtre en mode plein écran.
             *
             * Cette méthode doit permettre de passer la fenêtre en mode plein écran ou revenir
             * en mode normal.
             */
            virtual void FullScreenWindow() = 0;

        private:
            // Aucune donnée membre privée définie dans cette interface.
    };
}


