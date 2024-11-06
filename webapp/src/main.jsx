import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom'
import { Home } from './pages/home.jsx'

 
import { Layout } from './components/Layout.jsx'

createRoot(document.getElementById('root')).render(
  <StrictMode>
     <Layout>
    <Router>
      
        <Routes>
          <Route path="/" element={<Home />} />
        </Routes>
     
    </Router>
    </Layout>
  </StrictMode>,
)