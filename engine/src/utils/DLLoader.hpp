/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

// std
#include <string>
#include <stdexcept>
#include <dlfcn.h>
#include <memory>
#include <iostream>


    template <typename T>
    class DLLoader {
        public:
            /**
             * @brief Construct a new DLLoader object
             *
             */
            DLLoader() = default;

            /**
             * @brief Destroy the DLLoader object
             *
             */
            ~DLLoader() {
                if (_handle)
                    dlclose(_handle);
            }

            /**
             * @brief Get the Instance object
             *
             * Use this function to get an instance of the class.
             * Throws a runtime_error if the library cannot be opened or if the symbol cannot be loaded.
             *
             * @param path Path to the library.
             * @param entryPoint Name of the function to load.
             * @return std::shared_ptr<T>
             */
            std::shared_ptr<T> getInstance(const std::string &path, const std::string &entryPoint = "entryPoint")
            {
                _handle = dlopen(path.c_str(), RTLD_LAZY);
                if (!_handle) {
                    throw std::runtime_error("Cannot open library: " + std::string(dlerror()));
                }

                // Cast the symbol to a function that returns a pointer to T.
                void *(*create)() = (void *(*)())dlsym(_handle, entryPoint.c_str());
                if (!create) {
                    throw std::runtime_error("Cannot load symbol: " + std::string(dlerror()));
                }

                // Create an instance using the constructor function from the shared library
                T *instance = static_cast<T *>(create());

                return std::shared_ptr<T>(instance, [this](T *ptr) {
                    dlclose(_handle);
                    delete ptr;
                });
            }


            /**
             * @brief Destroy the Instance object
             *
             * @param instance
             */
            void destroyInstance(T *instance)
            {
                if (instance) {
                    delete instance;
                }
            }

        private:
            void *_handle = nullptr;
    };


#endif /* !DLLOADER_HPP_ */
