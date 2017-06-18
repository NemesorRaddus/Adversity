package org.qtproject.qt5.android.bindings;

import android.os.Bundle;
import android.os.Build;
import android.view.View;
import org.qtproject.qt5.android.bindings.QtActivity;

public class MyActivity extends QtActivity
{
    public static MyActivity s_activity = null;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        s_activity = this;
        super.onCreate(savedInstanceState);
    }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        s_activity = null;
    }
	@Override
    public void onWindowFocusChanged(boolean hasFocus)
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT)
        {
            if (hasFocus)
            {
                getWindow().getDecorView().setSystemUiVisibility(
                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                    | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                    | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                    | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                    | View.SYSTEM_UI_FLAG_FULLSCREEN
                    | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
            }
        }
        if (!QtApplication.invokeDelegate(hasFocus).invoked)
            super.onWindowFocusChanged(hasFocus);
    }
}
