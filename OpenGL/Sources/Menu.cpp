#include "Menu.hpp"

void Menu::Render(GLFWwindow* Window, const int Width, const int Height)
{
	ImGui::SetCursorPos(ImVec2(Width / 2 - Width / 12, 210 + Height / 6));
	if (ImGui::Button("Multithread", ImVec2(Width / 6, 50)))
	{
		gameState = GS_MULTITHREAD;
	}
	ImGui::SetCursorPos(ImVec2(Width / 2 - Width / 12, 270 + Height / 6));
	if (ImGui::Button("Options", ImVec2(Width/6, 50)))
	{
		gameState = GS_OPTION;
	}
	ImGui::SetCursorPos(ImVec2(Width / 2 - Width / 12, 330 + Height / 6));
	if (ImGui::Button("Quitter", ImVec2(Width/6, 50)))
	{
		glfwSetWindowShouldClose(Window, true);
	}

}

void Menu::RenderOption(Player &player, GLFWwindow* Window, const int Width, const int Height)
{
	
	ImGui::SetCursorPos(ImVec2(Width /2 - 75, 150 + Height / 6));
	if (ImGui::Button("forward", ImVec2(150, 50)))
	{
		selectButton = B_FORWARD;
		changeInput = true;
	
	}

	ImGui::SetWindowFontScale(2);
	ImGui::SetCursorPos(ImVec2(Width / 2 + 100, 160 + Height / 6));
	if(player.keyBoardInput.moveForward != 270)
		ImGui::Text(glfwGetKeyName(player.keyBoardInput.moveForward, 0));
	ImGui::SetWindowFontScale(1);

	ImGui::SetCursorPos(ImVec2(Width / 2 - 75, 210 + Height / 6));
	if (ImGui::Button("backward", ImVec2(150, 50)))
	{
		selectButton = B_BACKWARD;
		changeInput = true;
	}

	ImGui::SetWindowFontScale(2);
	ImGui::SetCursorPos(ImVec2(Width / 2 + 100, 220 + Height / 6));
	if (player.keyBoardInput.moveBackward != 270)
		ImGui::Text(glfwGetKeyName(player.keyBoardInput.moveBackward, 0));
	ImGui::SetWindowFontScale(1);

	ImGui::SetCursorPos(ImVec2(Width / 2 - 75, 270 + Height / 6));
	if (ImGui::Button("right", ImVec2(150, 50)))
	{
		selectButton = B_RIGHT;
		changeInput = true;
	}

	ImGui::SetWindowFontScale(2);
	ImGui::SetCursorPos(ImVec2(Width / 2 + 100, 280 + Height / 6));
	if (player.keyBoardInput.moveRight != 270)
		ImGui::Text(glfwGetKeyName(player.keyBoardInput.moveRight, 0));
	ImGui::SetWindowFontScale(1);

	ImGui::SetCursorPos(ImVec2(Width / 2 - 75, 330 + Height / 6));
	if (ImGui::Button("left", ImVec2(150, 50)))
	{
		selectButton = B_LEFT;
		changeInput = true;
	}

	ImGui::SetWindowFontScale(2);
	ImGui::SetCursorPos(ImVec2(Width / 2 + 100, 340 + Height / 6));
	if (player.keyBoardInput.moveLeft != 270)
		ImGui::Text(glfwGetKeyName(player.keyBoardInput.moveLeft, 0));
	ImGui::SetWindowFontScale(1);

	ImGui::SetCursorPos(ImVec2(Width / 2 - 75, 390 + Height / 6));
	if (ImGui::Button("jump", ImVec2(150, 50)))
	{
		selectButton = B_JUMP;
		changeInput = true;
	} 

	ImGui::SetWindowFontScale(2);
	if (player.keyBoardInput.moveUp == 32)
	{
		const char* space = "space";
		ImGui::SetCursorPos(ImVec2(Width / 2 + 100, 400 + Height / 6));
		ImGui::Text(space);
	}
	else
	{
		ImGui::SetCursorPos(ImVec2(Width / 2 + 100, 400 + Height / 6));
		if (player.keyBoardInput.moveUp != 270)
			ImGui::Text(glfwGetKeyName(player.keyBoardInput.moveUp, 0));
		
	}
	ImGui::SetWindowFontScale(1);

	if (changeInput)
	{
		switch (selectButton)
		{
		case B_FORWARD:
			lastKey = player.keyBoardInput.moveForward;
			//player.keyBoardInput.moveForward = checkKey(lastButtonPush(Window),player, lastKey);
			player.keyBoardInput.moveForward = lastButtonPush(Window);
			break;
		case B_BACKWARD:
			lastKey = player.keyBoardInput.moveBackward;
			player.keyBoardInput.moveBackward = lastButtonPush(Window);
			break;
		case B_LEFT:
			lastKey = player.keyBoardInput.moveLeft;
			player.keyBoardInput.moveLeft = lastButtonPush(Window);
			break;
		case B_RIGHT:
			lastKey = player.keyBoardInput.moveRight;
			player.keyBoardInput.moveRight = lastButtonPush(Window);
			break;
		case B_JUMP:
			lastKey = player.keyBoardInput.moveUp;
			player.keyBoardInput.moveUp = lastButtonPush(Window);
			break;
		default:
			break;
		}
	}

}

int Menu::checkKey(int key, Player& player, int lastKey)
{
	if (player.keyBoardInput.moveForward == key)
		return lastKey;
	if (player.keyBoardInput.moveBackward == key)
		return lastKey;
	if (player.keyBoardInput.moveLeft == key)
		return lastKey;
	if (player.keyBoardInput.moveRight == key)
		return lastKey;
	if (player.keyBoardInput.moveUp == key)
		return lastKey;
	return key;
}

int Menu::lastButtonPush(GLFWwindow* Window)
{
	int i = 0;
	for (i; i <= GLFW_KEY_END; i++)
	{
		if (glfwGetKey(Window, i) == GLFW_PRESS)
		{
			changeInput = false;
			return i;
		}
	}
	if (i == GLFW_KEY_END)
		lastButtonPush(Window);
	return i;
}
