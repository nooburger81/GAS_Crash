#include "GameplayTags/GASCCTags.h"

namespace GASCCTags
{
	namespace GASCCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "GASCCTags.GASCCAbilities.ActivateOnGiven", "Tag for Abilities that should activate immediately once given");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GASCCTags.GASCCAbilities.Primary", "Tag for the Primary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "GASCCTags.GASCCAbilities.Secondary", "Tag for the Secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "GASCCTags.GASCCAbilities.Tertiary", "Tag for the Tertiary Ability");
	}

	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GASCCTags.Events.Enemy.HitReact", "Tag for Enemy Hit React Events");
		}
	}
	
}
