package com.handyhome.app;

import android.content.Intent;

import androidx.annotation.NonNull;

import com.epicgames.unreal.SplashActivity;

import java.util.Objects;

import io.flutter.embedding.android.FlutterActivity;
import io.flutter.embedding.engine.FlutterEngine;
import io.flutter.plugin.common.MethodChannel;

public class FlutterMethodChannelActivity extends FlutterActivity {

    private static final String FLUTTER_METHOD_CHANNEL = "HANDY_HOME_METHOD_CHANNEL";

    public static NewEngineIntentBuilder withNewEngine() {
        return new NewEngineIntentBuilder(FlutterMethodChannelActivity.class);
    }

    @Override
    public void configureFlutterEngine(@NonNull FlutterEngine flutterEngine) {
        super.configureFlutterEngine(flutterEngine);
        new MethodChannel(flutterEngine.getDartExecutor(), FLUTTER_METHOD_CHANNEL).setMethodCallHandler((call, result) -> {
            if (Objects.equals(call.method, "startUnrealEngine")) {
                startActivity(new Intent(this, SplashActivity.class));
            }
        });
    }
}
