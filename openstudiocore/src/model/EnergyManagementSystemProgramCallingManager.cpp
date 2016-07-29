/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include "EnergyManagementSystemProgramCallingManager.hpp"
#include "EnergyManagementSystemProgramCallingManager_Impl.hpp"
#include "EnergyManagementSystemProgram.hpp"
#include "EnergyManagementSystemProgram_Impl.hpp"

#include <utilities/idd/IddFactory.hxx>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_EnergyManagementSystem_ProgramCallingManager_FieldEnums.hxx>

#include "../utilities/core/Assert.hpp"

#include "ModelExtensibleGroup.hpp"

namespace openstudio {
namespace model {

namespace detail {

  EnergyManagementSystemProgramCallingManager_Impl::EnergyManagementSystemProgramCallingManager_Impl(const IdfObject& idfObject,
                                                                                                     Model_Impl* model,
                                                                                                     bool keepHandle)
    : ModelObject_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == EnergyManagementSystemProgramCallingManager::iddObjectType());
  }

  EnergyManagementSystemProgramCallingManager_Impl::EnergyManagementSystemProgramCallingManager_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                                     Model_Impl* model,
                                                                                                     bool keepHandle)
    : ModelObject_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == EnergyManagementSystemProgramCallingManager::iddObjectType());
  }

  EnergyManagementSystemProgramCallingManager_Impl::EnergyManagementSystemProgramCallingManager_Impl(const EnergyManagementSystemProgramCallingManager_Impl& other,
                                                                                                     Model_Impl* model,
                                                                                                     bool keepHandle)
    : ModelObject_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& EnergyManagementSystemProgramCallingManager_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType EnergyManagementSystemProgramCallingManager_Impl::iddObjectType() const {
    return EnergyManagementSystemProgramCallingManager::iddObjectType();
  }

  boost::optional<std::string> EnergyManagementSystemProgramCallingManager_Impl::callingPoint() const {
    return getString(OS_EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint,true);
  }

  bool EnergyManagementSystemProgramCallingManager_Impl::setCallingPoint(const std::string& callingPoint) {
    bool result = setString(OS_EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint, callingPoint);
    return result;
  }

  std::vector<EnergyManagementSystemProgram> EnergyManagementSystemProgramCallingManager_Impl::programs() const {
    // loop through extensible groups and return vector of programs
    std::vector<EnergyManagementSystemProgram> result;
    auto groups = extensibleGroups();
    
    for (const auto & elem : groups) {
      WorkspaceExtensibleGroup group = elem.cast<WorkspaceExtensibleGroup>();
      boost::optional<WorkspaceObject> wo = group.getTarget(OS_EnergyManagementSystem_ProgramCallingManagerExtensibleFields::ProgramName);
      if (wo){
        EnergyManagementSystemProgram program = wo->cast<EnergyManagementSystemProgram>();
        result.push_back(program);
      }  
    }
    return result;
  }

  boost::optional<EnergyManagementSystemProgram> EnergyManagementSystemProgramCallingManager_Impl::getProgram(unsigned index) const {
    //TODO return program at index 
    boost::optional<EnergyManagementSystemProgram> result;
    auto groups = extensibleGroups();
    unsigned sizeOfGroup = numExtensibleGroups();

    //is this < or <=
    if ((index <= sizeOfGroup) && (!groups[index].empty())) {
      WorkspaceExtensibleGroup group = groups[index].cast<WorkspaceExtensibleGroup>();
      boost::optional<WorkspaceObject> wo = group.getTarget(OS_EnergyManagementSystem_ProgramCallingManagerExtensibleFields::ProgramName);
      if (wo) {
        EnergyManagementSystemProgram program = wo->cast<EnergyManagementSystemProgram>();
        result = program;
      }
    } else {
      //assert here?
      OS_ASSERT(false);
    }
    return result;
  }

  bool EnergyManagementSystemProgramCallingManager_Impl::eraseProgram(unsigned index) {
    //erase program at index
    bool result = false;
    auto groups = extensibleGroups();
    unsigned sizeOfGroup = numExtensibleGroups();

    //is this < or <=
    if (index <= sizeOfGroup) {
      eraseExtensibleGroup(index);
      result = true;
    }
    return result;
  }

  void EnergyManagementSystemProgramCallingManager_Impl::erasePrograms() {
    //erase all programs in this calling manager
    clearExtensibleGroups();
    
  }

  bool EnergyManagementSystemProgramCallingManager_Impl::insertProgram(const EnergyManagementSystemProgram& program, unsigned index) {
    //bool result = setString(OS_EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint, callingPoint);
    //TODO erase program at index
    bool result = true;
    return result;
  }

  bool EnergyManagementSystemProgramCallingManager_Impl::addProgram(const EnergyManagementSystemProgram& program) {
    //add program to end of vector of programs
    bool result = false;
    WorkspaceExtensibleGroup group = getObject<ModelObject>().pushExtensibleGroup().cast<WorkspaceExtensibleGroup>();
    result = group.setPointer(OS_EnergyManagementSystem_ProgramCallingManagerExtensibleFields::ProgramName, program.handle());
    return result;
  }

  bool EnergyManagementSystemProgramCallingManager_Impl::setProgram(const EnergyManagementSystemProgram& program, unsigned index) {
    //add program to {index} of vector of programs
    bool result = false;
    auto groups = extensibleGroups();
    unsigned sizeOfGroup = numExtensibleGroups();
    if (index <= sizeOfGroup) {
      //WorkspaceExtensibleGroup group = getObject<ModelObject>().insertExtensibleGroup().cast<WorkspaceExtensibleGroup>();
      //result = group.setPointer(OS_EnergyManagementSystem_ProgramCallingManagerExtensibleFields::ProgramName, program.handle());
      IdfExtensibleGroup idfGroup = insertExtensibleGroup(index, StringVector());
      OS_ASSERT(!idfGroup.empty());
      ModelExtensibleGroup group = idfGroup.cast<ModelExtensibleGroup>();
      bool result = group.setPointer(0, program.handle());
      OS_ASSERT(result); 
    }
    return result;
  }

  bool EnergyManagementSystemProgramCallingManager_Impl::setPrograms(const std::vector<const EnergyManagementSystemProgram>& programs) {
    //bool result = setString(OS_EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint, callingPoint);
    //TODO add programs to end of vector of programs
    bool result = true;
    return result;
  }

  std::vector<unsigned> EnergyManagementSystemProgramCallingManager_Impl::nullPrograms() const {
    //return getString(OS_EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint, true);
    //TODO return vector of indices of null programs in the program vector
    std::vector<unsigned> result;
    return result;
  }

  bool EnergyManagementSystemProgramCallingManager_Impl::removeNullPrograms() {
    //bool result = setString(OS_EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint, callingPoint);
    //TODO remove any null entries in the vector of programs
    bool result = true;
    return result;
  }
} // detail

EnergyManagementSystemProgramCallingManager::EnergyManagementSystemProgramCallingManager(const Model& model)
  : ModelObject(EnergyManagementSystemProgramCallingManager::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>());

  // TODO: Appropriately handle the following required object-list fields.
}

IddObjectType EnergyManagementSystemProgramCallingManager::iddObjectType() {
  return IddObjectType(IddObjectType::OS_EnergyManagementSystem_ProgramCallingManager);
}

std::vector<std::string> EnergyManagementSystemProgramCallingManager::validCallingPointValues() {
  return getIddKeyNames(IddFactory::instance().getObject(iddObjectType()).get(),
                        OS_EnergyManagementSystem_ProgramCallingManagerFields::EnergyPlusModelCallingPoint);
}

boost::optional<std::string> EnergyManagementSystemProgramCallingManager::callingPoint() const {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->callingPoint();
}

bool EnergyManagementSystemProgramCallingManager::setCallingPoint(const std::string& callingPoint) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->setCallingPoint(callingPoint);
}

std::vector<EnergyManagementSystemProgram> EnergyManagementSystemProgramCallingManager::programs() const {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->programs();
}

boost::optional<EnergyManagementSystemProgram> EnergyManagementSystemProgramCallingManager::getProgram(unsigned index) const {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->getProgram(index);
}

bool EnergyManagementSystemProgramCallingManager::eraseProgram(unsigned index) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->eraseProgram(index);
}

void EnergyManagementSystemProgramCallingManager::erasePrograms() {
  getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->erasePrograms();
}

bool EnergyManagementSystemProgramCallingManager::insertProgram(const EnergyManagementSystemProgram& program, unsigned index) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->insertProgram(program, index);
}

bool EnergyManagementSystemProgramCallingManager::addProgram(const EnergyManagementSystemProgram& program) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->addProgram(program);
}

bool EnergyManagementSystemProgramCallingManager::setProgram(const EnergyManagementSystemProgram& program, unsigned index) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->setProgram(program, index);
}

bool EnergyManagementSystemProgramCallingManager::setPrograms(const std::vector<const EnergyManagementSystemProgram>& programs) {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->setPrograms(programs);
}

std::vector<unsigned> EnergyManagementSystemProgramCallingManager::nullPrograms() const {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->nullPrograms();
}

bool EnergyManagementSystemProgramCallingManager::removeNullPrograms() {
  return getImpl<detail::EnergyManagementSystemProgramCallingManager_Impl>()->removeNullPrograms();
}

/// @cond
EnergyManagementSystemProgramCallingManager::EnergyManagementSystemProgramCallingManager(std::shared_ptr<detail::EnergyManagementSystemProgramCallingManager_Impl> impl)
  : ModelObject(impl)
{}
/// @endcond

} // model
} // openstudio
