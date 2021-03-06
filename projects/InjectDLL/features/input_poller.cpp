#include <common.h>
#include <constants.h>
#include <features/input_poller.h>

#include <interception_macros.h>
#include <map>
#include <vector>

// We might want to make this thread safe?

namespace {

    BINDING(11253376, app::Input_InputButtonProcessor*, Core_Input__GetButton, (int32_t button));

    struct InputData
    {
        InputState state;
        std::vector<input_callback> callbacks;
    };

    std::map<InputButton, InputData> input_data;

    STATIC_CLASS(71563216, app::Input_Cmd__Class*, input_cmd);

    void on_fixed_update(app::GameController* this_ptr)
    {
        if (!input_cmd_is_valid())
            return;

        auto processors = &(*input_cmd)->static_fields->AnyStart;
        auto count = static_cast<int>(InputButton::InputButton_LAST);
        for (auto i = 0; i < count; ++i)
        {
            auto button = static_cast<InputButton>(i);
            auto& data = input_data[button];
            data.state.button = button;

            auto old_pressed = data.state.pressed;
            auto input_processor = processors[i];
            if (input_processor != nullptr)
            {
                data.state.just_pressed = !input_processor->fields.WasPressed && input_processor->fields.IsPressed;
                data.state.pressed = input_processor->fields.IsPressed;
            }

            if (old_pressed || data.state.pressed)
                for (auto callback : data.callbacks)
                    callback(data.state);
        }

    }

    INTERCEPT(10044704, void, GameController_FixedUpdate, (app::GameController* this_ptr)) {
        GameController_FixedUpdate(this_ptr);
        on_fixed_update(this_ptr);
    }
}

InputState const& get_input_state(InputButton button)
{
    return input_data[button].state;
}

void register_input_callback(InputButton button, input_callback callback)
{
    auto& callbacks = input_data[button].callbacks;
    auto it = std::find(callbacks.begin(), callbacks.end(), callback);
    if (it == callbacks.end())
        callbacks.push_back(callback);
    else
        trace(MessageType::Error, 3, "game", "registering callback multiple times.");
}

bool unregister_input_callback(InputButton button, input_callback callback)
{
    auto& callbacks = input_data[button].callbacks;
    auto it = std::find(callbacks.begin(), callbacks.end(), callback);
    if (it != callbacks.end())
    {
        callbacks.erase(it);
        return true;
    }

    return false;
}
