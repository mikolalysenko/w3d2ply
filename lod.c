/*	Functions for handling W3D file LOD data
	Copyright 2004 Jonathan Wilson

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "w3d.h"
/*
Function to turn a string of the form hierarchyname.meshname into a string of the form meshname
inputs: string
outputs: converted string
*/
void StripHierarchyName(char *Name)
{
	uint32 Count = 0;
	uint32 Position = 0;
	for (Count = 0;Count < strlen(Name);Count++)
	{
		if (Name[Count] == '.')
		{
			break;
		}
	}
	Position = Count+1;
	for (Count = Position;Count < strlen(Name);Count++)
	{
		Name[Count-Position] = Name[Count];
	}
	Name[Count-Position] = '\0';
}
