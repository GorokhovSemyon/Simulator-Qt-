#ifndef EXCHANGE_STRUCTURES_H
#define EXCHANGE_STRUCTURES_H

#include "protocols/protocol_simulator.h"
#include "structures/targeting_structures.h"

/// это глобальная внутренняя структура, содержащая весь обмен пульта
/// здесь не должно быть "отсебятины" - набирать includ`ами из header`ов

struct Exchange_structures
{
    ToSimulator_protocol to_data;           //К Unity
    FromSimulator_protocol from_data;       //От Unity

    TargetingParams target_params;          //Задающие значения
};

#endif // EXCHANGE_STRUCTURES_H
