/*	Functions for loading W3D files into the internal data structures
	Copyright 2004 Jonathan Wilson

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
void LoadW3dFromDisk(char *Filename); //load a w3d file from disk
void LoadW3d(FILE *f,uint32 FileSize); //load a w3d file from inside another file (such as a MIX file)
