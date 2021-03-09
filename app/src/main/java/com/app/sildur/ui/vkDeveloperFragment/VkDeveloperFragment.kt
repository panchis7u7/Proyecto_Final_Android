package com.app.sildur.ui.vkDeveloperFragment

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import com.app.sildur.R

class VkDeveloperFragment : Fragment() {
    private lateinit var devViewModel: VkDeveloperViewModel

    override fun onCreateView(
            inflater: LayoutInflater,
            container: ViewGroup?,
            savedInstanceState: Bundle?
    ): View? {
        devViewModel =
                ViewModelProvider(this).get(VkDeveloperViewModel::class.java)
        val root = inflater.inflate(R.layout.vkdeveloper_fragment, container, false)
        val textView: TextView = root.findViewById(R.id.vk_message)
        devViewModel.text.observe(viewLifecycleOwner, Observer {
            textView.text = it
        })
        return root
    }
}