package com.app.sildur

import android.graphics.drawable.ColorDrawable
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.Menu
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.widget.Toolbar
import androidx.drawerlayout.widget.DrawerLayout
import androidx.navigation.NavArgument
import androidx.navigation.NavController
import androidx.navigation.findNavController
import androidx.navigation.ui.AppBarConfiguration
import androidx.navigation.ui.navigateUp
import androidx.navigation.ui.setupActionBarWithNavController
import androidx.navigation.ui.setupWithNavController
import com.google.android.material.floatingactionbutton.FloatingActionButton
import com.google.android.material.navigation.NavigationView
import com.google.android.material.snackbar.Snackbar
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.app_bar_main.*
import kotlinx.android.synthetic.main.vkdeveloper_fragment.*
import java.io.IOException

class MainActivity : AppCompatActivity() {

    private lateinit var  navController: NavController
    private lateinit var appBarConfiguration: AppBarConfiguration
    private lateinit var listener: NavController.OnDestinationChangedListener
    private lateinit var dev_message: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        try {
            dev_message = startVulkanJNI()
        } catch (e: IOException){
            Toast.makeText(this, "Error al inicializar vulkan!: ${e.message}", Toast.LENGTH_LONG)
        }

        val toolbar: Toolbar = toolbar
        setSupportActionBar(toolbar)

        //app_bar_main
        val fab: FloatingActionButton = fab
        fab.setOnClickListener { view ->
            Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                    .setAction("Action", null).show()
        }

        //Activity_main.xml
        val drawerLayout: DrawerLayout = drawer_layout
        //Activity_main.xml -> Nav_view
        val navView: NavigationView = nav_view
        //Content_main.xml
        navController = findNavController(R.id.nav_host_fragment)
        // Passing each menu ID as a set of Ids because each
        // menu should be considered as top level destinations.

        appBarConfiguration = AppBarConfiguration(navController.graph, drawerLayout)
        setupActionBarWithNavController(navController, appBarConfiguration)
        navView.setupWithNavController(navController)

        listener = NavController.OnDestinationChangedListener{controller, destination, arguments ->
            when(destination.id){
                R.id.nav_developer -> {
                    val argument = NavArgument.Builder().setDefaultValue(dev_message).build()
                    destination.addArgument("vkStatus", argument)
                }
            }
        }

        // Example of a call to a native method
        //vk_message.text = "Hola desde la main activity!"
        //vk_message.text = stringFromJNI()
    }

    override fun onResume() {
        super.onResume()
        navController.addOnDestinationChangedListener(listener)

    }

    override fun onPause() {
        super.onPause()
        navController.removeOnDestinationChangedListener(listener)
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.main, menu)
        return true
    }

    override fun onSupportNavigateUp(): Boolean {
        val navController = findNavController(R.id.nav_host_fragment)
        return navController.navigateUp(appBarConfiguration) || super.onSupportNavigateUp()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun startVulkanJNI(): String

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}