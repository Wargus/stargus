/*
 * IScript.h
 *
 *      Author: Andreas Volz
 */

#ifndef ISCRIPT_H
#define ISCRIPT_H

// project
#include "ObjectAccess.h"

namespace dat
{

class IScript: public ObjectAccess
{
public:
  IScript(DataHub &datahub, unsigned int id);
  virtual ~IScript();

  enum AnimationType
    {
      Init, // Initial animation
      Death, // Death animation
      GndAttkInit, // Initial ground attack animation
      AirAttkInit, // Initial air attack animation
      Unused1, // Unknown/unused animation
      GndAttkRpt, // Repeated ground attack animation
      AirAttkRpt, // Repeated air attack animation
      CastSpell, // Spell casting animation
      GndAttkToIdle, // Animation for returning to an idle state after a ground attack
      AirAttkToIdle, // Animation for returning to an idle state after an air attack
      Unused2, // Unknown/unused animation
      Walking, // Walking/moving animation
      WalkingToIdle, // Animation for returning to an idle state after walking/moving
      SpecialState1, // Some sort of category of special animations, in some cases an in-transit animation, sometimes used for special orders, sometimes having to do with the animation when something finishes morphing, or the first stage of a construction animation
      SpecialState2, // Some sort of category of special animations, in some cases a burrowed animation, sometimes used for special orders, sometimes having to do with the animation when canceling a morph, or the second stage of a construction animation
      AlmostBuilt, // An animation for one part of the building process
      Built, // Final animation before finishing being built
      Landing, // Landing animation
      LiftOff, // Lifting off animation
      IsWorking, // Animation for when researching an upgrade/technology or training/building units and some other animations for some sort of work being done
      WorkingToIdle, // Animation for returning to an idle state after IsWorking
      WarpIn, // Warping in animation
      Unused3, // Unknown/unused animation
      StarEditInit, // Previously called InitTurret, this is actually an alternate initial animation for StarEdit a.k.a. the Campaign Editor
      Disable, // Animation for becoming disabled, either through the "Set Doodad State" trigger action or by not being in the psi field of any pylons
      Burrow, // Burrowing animation
      UnBurrow, // Unburrowing animation
      Enable // Animation for becoming enabled, either through the "Set Doodad State" trigger action or by being in the psi field of a pylon
    };

  std::vector<iscript_bin_t::opcode_type_t*> getAnimationScript(IScript::AnimationType animationType);

  std::vector<iscript_bin_t::opcode_type_t*> getAnimationScript(unsigned int animationType);

  int8_t getAnimationCount();

  /**
   * @return true in case the iscript format is broodwar. (Nothing to do as the parser detects and handles the format itself)
   */
  bool is_format_bw();

private:

};

} /* namespace dat */

#endif /* ISCRIPT_H */
