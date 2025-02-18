//////////////////////////////////////////////////////////////////////////
// Copyright (C) 2024  Rohit Jairaj Singh (rohit@singh.org.in)          //
//                                                                      //
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//                                                                      //
// You should have received a copy of the GNU General Public License    //
// along with this program.  If not, see <https://www.gnu.org/licenses/ //
//////////////////////////////////////////////////////////////////////////
#include "Priority.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>

void SetPriority() {
#ifdef WIN32
    HANDLE process = GetCurrentProcess();
    DWORD_PTR processAffinityMask = 0x2;

    if (!SetProcessAffinityMask(process, processAffinityMask)) {
        std::cout << "Unable to set priority mask" << std::endl;
    }

    if (!SetPriorityClass(process, HIGH_PRIORITY_CLASS)) {
        std::cout << "Making priority highest" << std::endl;
    }
#endif
}