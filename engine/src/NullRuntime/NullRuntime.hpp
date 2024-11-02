/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef NULLRUNTIME_H
#define NULLRUNTIME_H

#include "IRuntime/IRuntime.hpp"
// std

namespace RType
{

class NullRuntime : public IRuntime
{
   public:
    NullRuntime() {}
    ~NullRuntime() {}

   private:
    // Member variables
};

}  // namespace RType

#endif  // NULLRUNTIME_H