#pragma once

enum PokemonType
{
	Normal,
	Fighting,
	Flying,
	Poison,
	Ground,
	Rock,
	Bug,
	Ghost,
	Steel,
	Fire,
	Water,
	Grass,
	Electric,
	Psychic,
	Ice,
	Dragon,
	Dark,
	Fairy,
	Cosmic,
	unknown
};

class CPokemon
{
	wstring m_Name;
	wstring m_InternalName;
	PokemonType m_Type1;
	PokemonType m_Type2;
	UINT m_BaseStats[6];
};

