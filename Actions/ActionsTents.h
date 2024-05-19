#pragma once

namespace Actions {
	class ActionsTents {
	public:
		DWORD mDeselectingTentAddr;
		char vanillaCode[6];
	public:
		ActionsTents();
		~ActionsTents();
		void ReadVanillaCode();
		void NopDeselectingTent();
		void SetVanillaCode();
	};
}