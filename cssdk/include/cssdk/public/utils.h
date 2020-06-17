// ***********************************************************************
// Created          : 04-01-2020
//
// Last Modified By : the_hunter
// Last Modified On : 05-26-2020
// ***********************************************************************
//     Copyright (c) 1996-2002, Valve LLC. All rights reserved.
// ***********************************************************************

#pragma once

#include <cssdk/engine/eiface.h>
#include <cssdk/engine/global_vars.h>

class EntityBase;

/// <summary>
/// </summary>
inline bool cssdk_is_client(const int index)
{
	return index > 0 && index <= g_global_vars->max_clients;
}

/// <summary>
/// </summary>
inline bool cssdk_is_client(Edict* entity)
{
	return cssdk_is_client(g_engine_funcs.index_of_edict(entity));
}

/// <summary>
/// </summary>
inline bool cssdk_is_valid_entity(const Edict* const entity)
{
	return entity && !entity->free && entity->private_data && !(entity->vars.flags & FL_KILL_ME);
}

/// <summary>
/// </summary>
template <typename T>
T cssdk_entity_private_data(const Edict* const entity)
{
	return entity == nullptr ? T() : static_cast<T>(entity->private_data);
}

/// <summary>
/// </summary>
inline const char* cssdk_entity_key_value(Edict* const entity, const char* key)
{
	auto* buffer = g_engine_funcs.get_info_key_buffer(entity);
	return g_engine_funcs.info_key_value(buffer, key);
}

/// <summary>
/// </summary>
inline const char* cssdk_entity_key_value(const int entity, const char* key)
{
	return cssdk_entity_key_value(g_engine_funcs.entity_of_ent_index(entity), key);
}

/// <summary>
/// </summary>
inline void cssdk_entity_set_key_value(Edict* const entity, const char* key, const char* value)
{
	const auto index = g_engine_funcs.index_of_edict(entity);
	auto* buffer = g_engine_funcs.get_info_key_buffer(entity);
	g_engine_funcs.set_client_key_value(index, buffer, key, value);
}

/// <summary>
/// </summary>
inline void cssdk_entity_set_key_value(const int entity, const char* key, const char* value)
{
	auto* edict = g_engine_funcs.entity_of_ent_index(entity);
	auto* buffer = g_engine_funcs.get_info_key_buffer(edict);
	g_engine_funcs.set_client_key_value(entity, buffer, key, value);
}

/// <summary>
/// </summary>
inline Vector cssdk_get_gun_position(const EntityVars& entity_vars)
{
	return entity_vars.origin + entity_vars.view_ofs;
}

/// <summary>
/// </summary>
inline void cssdk_get_gun_position(const EntityVars& entity_vars, Vector& position)
{
	position.x = entity_vars.origin.x + entity_vars.view_ofs.x;
	position.y = entity_vars.origin.y + entity_vars.view_ofs.y;
	position.z = entity_vars.origin.z + entity_vars.view_ofs.z;
}

/// <summary>
/// </summary>
bool cssdk_is_bot(Edict* client);

/// <summary>
/// </summary>
short cssdk_fixed_signed16(float value, float scale);

/// <summary>
/// </summary>
unsigned short cssdk_fixed_unsigned16(float value, float scale);

/// <summary>
/// </summary>
void cssdk_hud_message(EntityBase* entity, const HudTextParams& hud_params, const char* message, Edict* client = nullptr);

/// <summary>
/// </summary>
void cssdk_hud_message(Edict* client, const HudTextParams& hud_params, const char* message);

/// <summary>
/// </summary>
void cssdk_hud_message(int client, const HudTextParams& hud_params, const char* message);
