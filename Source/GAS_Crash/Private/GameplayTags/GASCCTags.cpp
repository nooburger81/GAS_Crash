#include "GameplayTags/GASCCTags.h"

namespace GASCCTags
{
	namespace GASCCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "GASCCTags.GASCCAbilities.ActivateOnGiven", "Tag for Abilities that should activate immediately once given");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GASCCTags.GASCCAbilities.Primary", "Tag for the Primary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "GASCCTags.GASCCAbilities.Secondary", "Tag for the Secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "GASCCTags.GASCCAbilities.Tertiary", "Tag for the Tertiary Ability");

		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "GASCCTags.GASCCAbilities.Enemy.Attack", "Tag for enemy attack abilities");
		}
	}

	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "GASCCTags.Events.KillScored", "Tag for the Enemy KillScored Event");
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GASCCTags.Events.Enemy.HitReact", "Tag for Enemy Hit React Events");
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack, "GASCCTags.Events.Enemy.EndAttack", "Tag for the Enemy Ending an Attack");
		}
	}
	
}
